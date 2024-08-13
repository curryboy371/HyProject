// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"

#include "GameplayTagContainer.h"


#include "HyTagManager.generated.h"


struct FGameplayTuple
{
	FGameplayTag Tag;
	FGameplayTagContainer Container;
};

struct FNormalActionTagSet
{
	FGameplayTag ActionParent;

	FGameplayTag ActionIdle;
	FGameplayTag ActionSpawn;
	FGameplayTag ActionWalk;
	FGameplayTag ActionRun;
	FGameplayTag ActionJump;
	FGameplayTag ActionEquip;
	FGameplayTag ActionUnEquip;
};

struct FAttackActionTagSet
{
	FGameplayTag ActionParent;
	FGameplayTag ActionAttack;
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


protected:
	void InitActionTagSet();

	void AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple);


public:
	FNormalActionTagSet NorActionTagSet;
	FAttackActionTagSet AttActionTagSet;
};
