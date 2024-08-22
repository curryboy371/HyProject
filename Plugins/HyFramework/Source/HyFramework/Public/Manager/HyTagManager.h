// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"

#include "GameplayTagContainer.h"

#include "CControlTypes.h"
#include "ActionsTypes.h"

#include "HyTagManager.generated.h"


struct FGameplayTuple
{
	FGameplayTag Tag;
	FGameplayTagContainer Container;
};

struct FActionExcuteSet
{
	FGameplayTag NorActionParent;
	FActionExcuteData ActionIdle;
	FActionExcuteData ActionSpawn;
	FActionExcuteData ActionMove;


	FGameplayTag DoingActionParent;
	FActionExcuteData ActionJump;
	FActionExcuteData ActionEquip;
	FActionExcuteData ActionUnEquip;
	FActionExcuteData ActionCrouching;

	FGameplayTag AttActionParent;
	FActionExcuteData ActionAttack;
};

struct FItemSlotTagSet
{
	FGameplayTag SlotParent;
	FGameplayTag SlotWeapon;
};



/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyTagManager : public UHyManagerBase
{
	GENERATED_BODY()

public:
	// UHyManagerBase을(를) 통해 상속됨
	void InitManager() override;
	void ReleaseManager() override;

public:

protected:
	void InitTagSet();
	

	void AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddActionTag(const FName& InTagName, FActionExcuteData& InActionExcuteData, EActionPriority InActionProperty = EActionPriority::EEmpty);


	void AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple);

public:
	// Check State By ActionTag
	const bool IsNormalAction(const FGameplayTag& InActionTag) const;
	const bool IsDoingAction(const FGameplayTag& InActionTag) const;
	const bool IsAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsDeadAction(const FGameplayTag& InActionTag) const;


public:
	FActionExcuteSet ActionExcuteSet;

	FItemSlotTagSet ItemSlotTagSet;



	FGameplayTagContainer DeadContainer;

protected:
};
