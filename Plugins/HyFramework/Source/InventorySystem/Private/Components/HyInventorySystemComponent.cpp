// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyInventorySystemComponent.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


#include "Items/HyWeapon.h"

#include "HyCoreMacro.h"

// Sets default values for this component's properties
UHyInventorySystemComponent::UHyInventorySystemComponent()
{
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

void UHyInventorySystemComponent::AttachWeaponOnBody(TObjectPtr<class AHyWeapon> InWeaponToEquip)
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

	const FName socket = InWeaponToEquip->GetBodySocketName();

	if (socket != NAME_None) 
	{
		if (InWeaponToEquip->AttachToComponent(CharacterOwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, socket) == false)
		{
			ERR_V("AttachToComponent failed Check Socket Name %s", *InWeaponToEquip->GetBodySocketName().ToString());
		}
	}
	else 
	{
		ERR_V("BodySocketName is nullptr");
	}

}

void UHyInventorySystemComponent::AttachWeaponOnHand(TObjectPtr<class AHyWeapon> InWeaponToEquip)
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

	const FName socket = InWeaponToEquip->GetHandSocketName();

	if (socket != NAME_None)
	{
		if (InWeaponToEquip->AttachToComponent(CharacterOwnerMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, socket) == false)
		{
			ERR_V("AttachToComponent failed Check Socket Name %s", *InWeaponToEquip->GetBodySocketName().ToString());
		}
	}
	else
	{
		ERR_V("HandSocketName is nullptr");
	}

}

