// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HyActorComponent.h"
#include "GameplayTagContainer.h"

#include "InvenTypes.h"
#include "Items/HyItem.h"


#include "Table/Item_TableEntity.h"



#include "HyInventorySystemComponent.generated.h"



USTRUCT(BlueprintType)
struct FInventoryItem : public FBaseItem
{
    GENERATED_BODY()

public:
    FInventoryItem()
        : FBaseItem()
        , ItemTableEntity(FItem_TableEntity())
        , bIsEquipped(false)
    {

    }

    FInventoryItem(const TSubclassOf<class AHyItem>& InItem, const FItem_TableEntity& InItemTableEntity, int32 InCount = 1)
        : FBaseItem(InItem, InCount)
        , ItemTableEntity(InItemTableEntity)
        , bIsEquipped(false)
    {

    }


    const FGameplayTag& GetEquipmentSlot() const
	{
		return ItemTableEntity.EquipmentSlot;
	}

    UPROPERTY(BlueprintReadWrite, Category = Inven)
    FItem_TableEntity ItemTableEntity;

    UPROPERTY(BlueprintReadWrite, Category = Inven)
    bool bIsEquipped;
};


USTRUCT(BlueprintType)
struct FEquippedItem 
{
    GENERATED_BODY()

public:
    FEquippedItem() 
    {
		InventoryItem = FInventoryItem();
		Item = nullptr;
    };

    FEquippedItem(const FInventoryItem& InInvenItem, TObjectPtr<class AHyItem> InItem)
    {
        InventoryItem = InInvenItem;
        InventoryItem.bIsEquipped = true;
        Item = InItem;
    }

    UPROPERTY(BlueprintReadWrite, Category = Inven)
    FInventoryItem InventoryItem;

    UPROPERTY(BlueprintReadOnly, Category = Inven)
    TObjectPtr<class AHyItem> Item;

    const FGameplayTag& GetItemSlot() const
    {
        return InventoryItem.GetEquipmentSlot();
    }

    FORCEINLINE bool operator==(const FEquippedItem& Other) const
    {
        return this->InventoryItem.GetEquipmentSlot() == Other.InventoryItem.GetEquipmentSlot();
    }

    FORCEINLINE bool operator!=(const FEquippedItem& Other) const
    {
        return this->InventoryItem.GetEquipmentSlot() != Other.InventoryItem.GetEquipmentSlot();
    }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const
    {
        return this->InventoryItem.GetEquipmentSlot() == Other;
    }

    FORCEINLINE bool operator!=(const FGameplayTag& Other) const
    {
        return this->InventoryItem.GetEquipmentSlot() != Other;
    }
};

USTRUCT(BlueprintType)
struct FEquipment 
{
	GENERATED_BODY()
public:
    FEquipment()
    {
		EquippedItems.Empty();
		EquipWeapon = nullptr;
	}

public:
    UPROPERTY(BlueprintReadOnly, Category = Inven)
    TArray<FEquippedItem> EquippedItems;

    UPROPERTY(BlueprintReadOnly, Category = Inven)
    TObjectPtr<class AHyWeapon> EquipWeapon;
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UHyInventorySystemComponent : public UHyActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UHyActorComponent을(를) 통해 상속됨
    virtual void  InitializeHyActorComponent() override;


    void AddInventoryItem(const FInventoryItem& InItem);
    void AddInventoryItem(const FItem_TableEntity& InItemTableEntity, const int32 InItemCount = 1);

    void EquipItemBySlot(const FGameplayTag& InSlotTag);
    void UnEquipItemBySlot(const FGameplayTag& InSlotTag);
    void UnEquipAllItems();


    bool IsEquippedSlot(const FGameplayTag& InSlotTag);
    bool IsEquippedSlot(const FGameplayTag& InSlotTag, TObjectPtr<class AHyItem> OutEquipItem);


public:
	void AttachWeapon(EWeaponArmState InWeaponArmState, TObjectPtr<class AHyWeapon> InWeaponToEquip);
    void AttachSubWeapon(TObjectPtr<class AHyWeapon> InWeaponToEquip);

public:
    const EWeaponArmState GetWeaponArmState() const { return WeaponArmState; }

    TObjectPtr<class AHyWeapon> GetEquippedWeapon() const { return Equipments.EquipWeapon; }

protected:
	void SetCharacterOwnerMesh(TObjectPtr<class USkeletalMeshComponent> InCharacterOwnerMesh) { CharacterOwnerMesh = InCharacterOwnerMesh; }



protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inven")
	TObjectPtr<class USkeletalMeshComponent> CharacterOwnerMesh;

    UPROPERTY(BlueprintReadOnly, Category = "Inven")
    EWeaponArmState WeaponArmState;

	TArray<FInventoryItem> InventoryItems;
	FEquipment Equipments;




};
