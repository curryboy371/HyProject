// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ActionsTypes.h"
#include "GameplayTagContainer.h"

#include "ActionsCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActionsCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONSSYSTEM_API IActionsCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext = "", bool bCanBeStored = false) { return false; };
	virtual void SetStoredAction(FActionExcuteData& InActionExcuteData, const FString InContext = "", bool bForce = false) {};
	virtual void HandleAction(EActionHandleType InExitType, float BlendOut = 0.5f) {};

	virtual void SetPerformingActionPriority(EActionPriority InPriority) {};

	virtual bool CompareCurrentPriority(EActionPriority InPriority) const { return false; }
	virtual const bool IsEmptyStoredAction() const { return false; };
	virtual const bool IsCanStoreAction(EActionPriority InPriority) const { return false; };


	virtual const FGameplayTag GetCurAction() const { return FGameplayTag::EmptyTag; }
	virtual const FGameplayTag GetStoredAction() const { return FGameplayTag::EmptyTag; }

};
