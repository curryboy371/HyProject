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
	FActionExcuteData ActionWalk;
	FActionExcuteData ActionRun;
	FActionExcuteData ActionJump;
	FActionExcuteData ActionEquip;
	FActionExcuteData ActionUnEquip;

	FGameplayTag AttActionParent;
	FActionExcuteData ActionAttack;
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
	void InitActionTagSet();

	void AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddActionTag(const FName& InTagName, FActionExcuteData& InActionExcuteData, EActionPriority InActionProperty = EActionPriority::EEmpty);


	void AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst, EActionPriority InActionProperty = EActionPriority::EEmpty);
	void AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple, EActionPriority InActionProperty = EActionPriority::EEmpty);


public:
	FActionExcuteSet ActionExcuteSet;


protected:
};
