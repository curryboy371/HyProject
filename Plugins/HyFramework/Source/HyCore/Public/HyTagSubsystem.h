// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "GameplayTagContainer.h"
#include "HyTagSubsystem.generated.h"


/**
 *   GameplayTag로 상태나 타입 등을 확인하는 기능의 서브 시스템
 *   
 */

struct FGameplayTuple
{
	FGameplayTag Tag;
	FGameplayTagContainer Container;
};

struct FActionTagSet
{
	FGameplayTag NorActionParent;
	FGameplayTag ActionIdle;
	FGameplayTag ActionSpawn;
	FGameplayTag ActionMove;

	FGameplayTag DoingActionParent;
	FGameplayTag ActionJump;
	FGameplayTag ActionEquip;
	FGameplayTag ActionUnEquip;
	FGameplayTag ActionCrouching;

	FGameplayTag AttActionParent;
	FGameplayTag ActionAttack;
	FGameplayTag ActionDashAttack;

};

struct FItemSlotTagSet
{
	FGameplayTag SlotParent;
	FGameplayTag SlotWeapon;
};

struct FCharacterTagSet
{
	FGameplayTag CharacterParent;
	FGameplayTag PlayerTag;
	FGameplayTag MonsterTag;
};


UCLASS()
class HYCORE_API UHyTagSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	UHyTagSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	void InitTagSet();
	void AddTag(const FName& InTagName, FGameplayTag& InActionTagInst);
	void AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple);

public:
	// Check State By ActionTag
	const bool IsNormalAction(const FGameplayTag& InActionTag) const;
	const bool IsDoingAction(const FGameplayTag& InActionTag) const;
	const bool IsAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsDeadAction(const FGameplayTag& InActionTag) const;


public:
	// check character type
	const bool IsPlayerCharacter(const FGameplayTag& InCharacterTag) const;
	const bool IsMonsterCharacter(const FGameplayTag& InCharacterTag) const;

	// check ai or user control
	const bool IsUserPlaying(const FGameplayTag& InEquipTag) const;
	const bool IsAIPlaying(const FGameplayTag& InEquipTag) const;

public:
	FActionTagSet ActionTagSet;
	FItemSlotTagSet ItemSlotTagSet;

	FGameplayTagContainer DeadContainer;

protected:
	FCharacterTagSet CharacterTagSet;

	FGameplayTag EquipPlayerParent;
	FGameplayTag EquipAIParent;
};
