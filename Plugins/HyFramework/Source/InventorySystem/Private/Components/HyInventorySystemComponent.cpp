// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyInventorySystemComponent.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


#include "Items/HyWeapon.h"

#include "GameplayTagContainer.h"

#include "HyCoreMacro.h"

// Sets default values for this component's properties
UHyInventorySystemComponent::UHyInventorySystemComponent()
{

	WeaponArmState = EWeaponArmState::EWS_None;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHyInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHyInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHyInventorySystemComponent::InitializeHyActorComponent()
{
	Super::InitializeHyActorComponent();

	if(GetOwner() == nullptr)
	{
		ERR_V("GetOwner is nullptr");
		return;
	}

	CharacterOwnerMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
}

void UHyInventorySystemComponent::AddInventoryItem(const FInventoryItem& InItem)
{
	if (InItem.Count <= 0)
	{
		ERR_V("InItem.Count is less than 0");
		return;
	}

	if(InItem.ItemClass == nullptr)
	{
		ERR_V("InItem.ItemClass is nullptr");
		return;
	}

	InventoryItems.Add(InItem);
}

void UHyInventorySystemComponent::AddInventoryItem(const FItem_TableEntity& InItemTableEntity, const int32 InItemCount/* = 1*/)
{
	if (InItemTableEntity.ItemID <= 0)
	{
		ERR_V("InItemTableEntity.ItemID is less than 0");
		return;
	}

	if (InItemCount <= 0)
	{
		ERR_V("InItemCount is less than 0");
		return;
	}

	if (UClass* ItemClass = StaticLoadClass(AHyItem::StaticClass(), nullptr, *InItemTableEntity.ItemPath))
	{
		const FInventoryItem NewInventoryItem(ItemClass, InItemTableEntity);
		InventoryItems.Add(NewInventoryItem);
	}
	else
	{
		ERR_V("ItemClass is nullptr %s ", *InItemTableEntity.ItemPath);
	}
}


void UHyInventorySystemComponent::EquipItemBySlot(const FGameplayTag& InSlotTag)
{
	// TODO 임시코드
	if(InventoryItems.Num() <= 0)
	{
		ERR_V("InventoryItems.Num() is less than 0");
		return;
	}

	for (int32 i = 0; i < InventoryItems.Num(); i++)
	{
		if (!Equipments.EquippedItems.Contains(InSlotTag) && InventoryItems[i].GetEquipmentSlot() == InSlotTag)
		{
			if (InventoryItems[i].ItemClass == nullptr)
			{
				ERR_V("InventoryItems[%d].ItemClass is nullptr", i);
				return;
			}

			if (TObjectPtr<AHyItem> SpawnedItem = GetWorld()->SpawnActor<AHyItem>(InventoryItems[i].ItemClass.Get()))
			{
				SpawnedItem->InitializeItem(&InventoryItems[i].ItemTableEntity);
				if (SpawnedItem->IsA(AHyWeapon::StaticClass()))
				{
					if (TObjectPtr<AHyWeapon> EquipWeapon = Cast<AHyWeapon>(SpawnedItem))
					{
						Equipments.EquipWeapon = EquipWeapon;
						AttachWeapon(EWeaponArmState::EWS_Unarmed, EquipWeapon);
						AttachSubWeapon(EquipWeapon);
						EquipWeapon->SetActorHiddenInGame(false);
					}
				}
				Equipments.EquippedItems.Add(FEquippedItem(InventoryItems[i], SpawnedItem));
			}
			else
			{
				ERR_V("EquipWeapon is nullptr");
			}
		}
	}

}

void UHyInventorySystemComponent::UnEquipItemBySlot(const FGameplayTag& InSlotTag)
{
	int32 DestroyIndex = -1;
	for (int32 i = 0; i < Equipments.EquippedItems.Num(); i++)
	{
		if (Equipments.EquippedItems[i].InventoryItem.ItemClass)
		{
			if (Equipments.EquippedItems[i].InventoryItem.GetEquipmentSlot() == InSlotTag)
			{
				Equipments.EquippedItems[i].Item->Destroy();
				Equipments.EquipWeapon = nullptr;
				DestroyIndex = i;
				break;
			}
		}
	}

	if(DestroyIndex != -1)
	{
		Equipments.EquippedItems.RemoveAt(DestroyIndex);
	}
}

void UHyInventorySystemComponent::UnEquipAllItems()
{
	for(int32 i = 0; i < Equipments.EquippedItems.Num(); i++)
	{
		if (Equipments.EquippedItems[i].Item)
		{
			Equipments.EquippedItems[i].Item->Destroy();
		}
	}

	Equipments.EquippedItems.Empty();

	WeaponArmState = EWeaponArmState::EWS_None;
}

bool UHyInventorySystemComponent::IsEquippedSlot(const FGameplayTag& InSlotTag)
{
	for (int32 i = 0; i < Equipments.EquippedItems.Num(); ++i)
	{
		if (Equipments.EquippedItems[i].InventoryItem.GetEquipmentSlot() == InSlotTag)
		{
			return true;
		}
	}

	return false;
}

bool UHyInventorySystemComponent::IsEquippedSlot(const FGameplayTag& InSlotTag, TObjectPtr<class AHyItem> OutEquipItem)
{
	OutEquipItem = nullptr;
	for (int32 i = 0; i < Equipments.EquippedItems.Num(); ++i)
	{
		if (Equipments.EquippedItems[i].InventoryItem.GetEquipmentSlot() == InSlotTag)
		{
			OutEquipItem = Equipments.EquippedItems[i].Item;
			return true;
		}
	}

	return false;
}

void UHyInventorySystemComponent::AttachWeapon(EWeaponArmState InWeaponArmState, TObjectPtr<class AHyWeapon> InWeaponToEquip)
{
	if (!CharacterOwnerMesh)
	{
		ERR_V("CharacterOwnerMesh is nullptr");
		return;
	}

	if (!InWeaponToEquip)
	{
		ERR_V("InWeaponToEquip is nullptr");
		return;
	}

	if(InWeaponArmState == EWeaponArmState::EWS_None)
	{
		ERR_V("InWeaponArmState is EWS_None");
		return;
	}

	FName socket = NAME_None;
	if (InWeaponArmState == EWeaponArmState::EWS_Armed)
	{
		socket = InWeaponToEquip->GetHandSocketName();
	}
	else if (InWeaponArmState == EWeaponArmState::EWS_Unarmed)
	{
		socket = InWeaponToEquip->GetBodySocketName();
	}

	if (socket == NAME_None)
	{
		ERR_V("socket is NAME_None");
		return;
	}

	if (USceneComponent* RootComp = InWeaponToEquip->GetRootComponent())
	{
		if (RootComp->AttachToComponent(CharacterOwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, socket) == false)
		{
			ERR_V("AttachToComponent failed Check Socket Name %s", *InWeaponToEquip->GetSubHandSocketName().ToString());
			return;
		}
	}

	WeaponArmState = InWeaponArmState;
}

void UHyInventorySystemComponent::AttachSubWeapon(TObjectPtr<class AHyWeapon> InWeaponToEquip)
{
	if (!CharacterOwnerMesh)
	{
		ERR_V("CharacterOwnerMesh is nullptr");
		return;
	}

	if (!InWeaponToEquip)
	{
		ERR_V("InWeaponToEquip is nullptr");
		return;
	}

	if (WeaponArmState == EWeaponArmState::EWS_None)
	{
		ERR_V("InWeaponArmState is EWS_None");
		return;
	}

	const FName socket = InWeaponToEquip->GetSubHandSocketName();

	if (socket == NAME_None)
	{
		ERR_V("socket is NAME_None");
		return;
	}

	if (USceneComponent* SubHandleComp = InWeaponToEquip->GetSubHandleComp())
	{
		if (SubHandleComp->AttachToComponent(CharacterOwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, socket) == false)
		{
			ERR_V("AttachToComponent failed Check Socket Name %s", *InWeaponToEquip->GetSubHandSocketName().ToString());
			return;
		}
	}
}
