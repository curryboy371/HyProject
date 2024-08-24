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

struct FActionLocationTagSet
{
	FGameplayTag StandActionTag;
	FGameplayTag DownActionTag;
	FGameplayTag InAirActionTag;
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
	const bool IsComboAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsDashAttackAction(const FGameplayTag& InActionTag) const;


	const bool IsDeadAction(const FGameplayTag& InActionTag) const;

	const bool IsStandAction(const FGameplayTag& InActionTag) const;
	const bool IsDownAction(const FGameplayTag& InActionTag) const;
	const bool IsInAirAction(const FGameplayTag& InActionTag) const;

	// DamageType To ActionType
	const FGameplayTag GetActionTypeByDamageType(const FGameplayTag& InDamageType, const FGameplayTag& CurActionTag) const;
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

	FCharacterTagSet CharacterTagSet;

protected:

	FGameplayTag EquipPlayerParent;
	FGameplayTag EquipAIParent;

	FActionLocationTagSet ActionLocationTagSet;


public:
	static FGameplayTag DefaultHitTag;

};
