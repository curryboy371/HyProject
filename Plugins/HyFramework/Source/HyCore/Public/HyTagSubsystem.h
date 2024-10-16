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


struct FActionTagSet
{
	FGameplayTag NorActionParent;
	FGameplayTag NorAirActionParent;
	FGameplayTag ActionIdle;
	FGameplayTag ActionAirIdle;
	FGameplayTag ActionSpawn;
	FGameplayTag ActionMove;

	FGameplayTag DoingActionParent;
	FGameplayTag ActionJump;
	FGameplayTag ActionEquip;
	FGameplayTag ActionUnEquip;
	FGameplayTag ActionCrouching;

	FGameplayTag ActionDash;


	FGameplayTag AttActionParent;
	FGameplayTag ActionAttack;
	FGameplayTag ActionJumpAttack;
	FGameplayTag ActionChargeAttack;
	FGameplayTag ActionDashAttack;




	FGameplayTag ActionAirAttackParent;
	FGameplayTag ActionAirStartAttacking; // air Start 
	FGameplayTag ActionAirAttacking; // air Combo


	FGameplayTag SkillActionParent;
	FGameplayTag ActionSlide;
	FGameplayTag ActionAvoid;
	FGameplayTag ActionDodge;

	FGameplayTag ActionSkill1;
	FGameplayTag ActionSkill2;
	FGameplayTag ActionSkill3;
	FGameplayTag ActionSkill4;
	FGameplayTag ActionSkill5;
	FGameplayTag ActionUlti;
};

struct FActionLocationTagSet
{
	FGameplayTag StandActionTag;
	FGameplayTag DownActionTag;
	FGameplayTag InAirActionTag;
};


struct FHitTagSet
{
	FGameplayTag DamagedStanding;
	FGameplayTag DamagedDown;

	FGameplayTag DamagedDead;
	FGameplayTag DamagedNormal;
	FGameplayTag DamagedLarge;
	FGameplayTag DamagedCritical;
	FGameplayTag DamagedAirLaunch; // Air상태로 만드는 Hit

	FGameplayTag DamagedInAir; // Air 상태 유지

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
	void AddContainerTag(const FName& InTagName, FGameplayTagContainer& InTagContainer);

public:
	// Check State By ActionTag
	const bool IsNormalAction(const FGameplayTag& InActionTag) const;
	const bool IsDoingAction(const FGameplayTag& InActionTag) const;

	const bool IsJumpAction(const FGameplayTag& InActionTag) const;

	const bool IsMoveAction(const FGameplayTag& InActionTag) const;

	const bool IsSkillAction(const FGameplayTag& InActionTag) const;
	const bool IsDodgeAction(const FGameplayTag& InActionTag) const;


	const bool IsAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsComboAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsDashAttackAction(const FGameplayTag& InActionTag) const;
	const bool IsChargeAttackAction(const FGameplayTag& InActionTag) const;


	const bool IsDeadAction(const FGameplayTag& InActionTag) const;

	const bool IsStandAction(const FGameplayTag& InActionTag) const;
	const bool IsDownAction(const FGameplayTag& InActionTag) const;
	const bool IsInAirAction(const FGameplayTag& InActionTag) const;

	const bool IsDamagedAction(const FGameplayTag& InActionTag) const;

	// DamageType To ActionType
	const FGameplayTag GetActionTypeByDamageType(const FGameplayTag& InDamageType, const FGameplayTag& CurActionTag) const;

	const bool IsNormalHit (const FGameplayTag& InDamageType) const;
	const bool IsLargeHit(const FGameplayTag& InDamageType) const;
	const bool IsCriticalHit(const FGameplayTag& InDamageType) const;


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
	FGameplayTagContainer DamagedParentContainer;
	FHitTagSet HitTagSet;

	FCharacterTagSet CharacterTagSet;

	FActionLocationTagSet ActionLocationTagSet;

protected:

	FGameplayTag EquipPlayerParent;
	FGameplayTag EquipAIParent;




public:
	static FGameplayTag DefaultHitTag;

};
