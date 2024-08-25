// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_Equip.h"
#include "Actors/Character/HyCharacterBase.h"
#include "Components/HyInventorySystemComponent.h"
#include "InvenTypes.h"

#include "HyCoreMacro.h"

void UHyAction_Equip::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);


	if (HyCharacterOwner)
	{
		if (HyCharacterOwner->IsCrouching())
		{
			MontageSectionName = TEXT("Crouch");
		}
		else
		{
			MontageSectionName = *InContext;
		}

		HyCharacterOwner->SetCombatMode(true);
	}


}

void UHyAction_Equip::OnActionSetupCompleted_Implementation(const FString& InContext)
{
	Super::OnActionSetupCompleted_Implementation(InContext);

}

void UHyAction_Equip::OnActionEnded_Implementation()
{
	Super::OnActionEnded_Implementation();


}

void UHyAction_Equip::OnActionTransition_Implementation(UActionsBaseAction* InPreAction)
{
	Super::OnActionTransition_Implementation(InPreAction);

}

void UHyAction_Equip::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);

}

void UHyAction_Equip::OnActionNotify_Implementation()
{
	if (!HyCharacterOwner)
	{
		ERR_V("HyCharacterOwner is nullptr");
	}

	if (!HyCharacterOwner->IsWeaponOnHand())
	{
		if (TObjectPtr<class UHyInventorySystemComponent> InventoryComp = HyCharacterOwner->GetInventorySystemComp())
		{
			InventoryComp->AttachWeapon(EWeaponArmState::EWS_Armed, InventoryComp->GetEquippedWeapon());
		}
	}
}

bool UHyAction_Equip::IsStopConditional_Implementation()
{
	return true;
}
