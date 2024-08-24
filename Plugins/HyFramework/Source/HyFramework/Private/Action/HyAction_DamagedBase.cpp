// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/HyAction_DamagedBase.h"

void UHyAction_DamagedBase::OnActionStarted_Implementation(const FString& InContext)
{
	Super::OnActionStarted_Implementation(InContext);
	

}

void UHyAction_DamagedBase::OnActionEnded_Implementation()
{
	OnActionEnded_Implementation();


}

void UHyAction_DamagedBase::OnActionTransition_Implementation(UActionsBaseAction* InpreAction)
{
	OnActionTransition_Implementation(InpreAction);


}

void UHyAction_DamagedBase::OnTick_Implementation(float DeltaTime)
{
	OnTick_Implementation(DeltaTime);


}

FName UHyAction_DamagedBase::GetMontageSectionName_Implementation()
{


	return FName();
}
