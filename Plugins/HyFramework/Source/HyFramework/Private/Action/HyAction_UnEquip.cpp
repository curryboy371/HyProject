// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_UnEquip.h"
#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyInventorySystemComponent.h"



void UHyAction_UnEquip::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);

	if (HyCharacterOwner)
	{
		HyCharacterOwner->SetCombatMode(false);
	}
}

void UHyAction_UnEquip::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_UnEquip::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_UnEquip::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	Super::OnActionTransition_Implementation(InpreAction);

}

void UHyAction_UnEquip::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

	if (ActionDuration > 0.1)
	{
		if (HyCharacterOwner)
		{
			if (HyCharacterOwner->IsWeaponOnHand())
			{
				if (TObjectPtr<class UHyInventorySystemComponent> InventoryComp = HyCharacterOwner->GetInventorySystemComp())
				{
					InventoryComp->AttachWeaponOnBody(InventoryComp->GetEquippedWeapon());
				}

			}
		}
	}

}

bool UHyAction_UnEquip::IsStopConditional_Implementation()
{
	return true;
}
