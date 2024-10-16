// Fill out your copyright notice in the Description page of Project Settings.


#include "HyTagSubsystem.h"

// 편리한 사용을 위해 디폴트 태그 설정
FGameplayTag UHyTagSubsystem::DefaultHitTag = FGameplayTag::RequestGameplayTag(FName("Damaged.Hit"));

UHyTagSubsystem::UHyTagSubsystem()
{


}

void UHyTagSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InitTagSet();

}

void UHyTagSubsystem::Deinitialize()
{
}

void UHyTagSubsystem::InitTagSet()
{
    AddTag(FName("Action.Stand.Normal"), ActionTagSet.NorActionParent);
    AddTag(FName("Action.Stand.Normal.Spawn"), ActionTagSet.ActionSpawn);
    AddTag(FName("Action.Stand.Normal.Idle"), ActionTagSet.ActionIdle);
    AddTag(FName("Action.Stand.Normal.Move"), ActionTagSet.ActionMove);

    AddTag(FName("Action.InAir.Normal"), ActionTagSet.NorAirActionParent);
    AddTag(FName("Action.InAir.Normal.Idle"), ActionTagSet.ActionAirIdle);


    AddTag(FName("Action.Stand.Doing"), ActionTagSet.DoingActionParent);
    AddTag(FName("Action.Stand.Doing.Jump"), ActionTagSet.ActionJump);
    AddTag(FName("Action.Stand.Doing.Equip"), ActionTagSet.ActionEquip);
    AddTag(FName("Action.Stand.Doing.UnEquip"), ActionTagSet.ActionUnEquip);
    AddTag(FName("Action.Stand.Doing.Crouching"), ActionTagSet.ActionCrouching);
    AddTag(FName("Action.Stand.Doing.Dash"), ActionTagSet.ActionDash);

    AddTag(FName("Action.Stand.Attack"), ActionTagSet.AttActionParent);
    AddTag(FName("Action.Stand.Attack.Attacking"), ActionTagSet.ActionAttack);
    AddTag(FName("Action.Stand.Attack.DashAttacking"), ActionTagSet.ActionDashAttack);
    AddTag(FName("Action.Stand.Attack.JumpAttacking"), ActionTagSet.ActionJumpAttack);
    AddTag(FName("Action.Stand.Attack.ChargeAttacking"), ActionTagSet.ActionChargeAttack);


    AddTag(FName("Action.InAir.Attack"), ActionTagSet.ActionAirAttackParent);
    AddTag(FName("Action.InAir.Attack.AirStartAttacking"), ActionTagSet.ActionAirStartAttacking);
    AddTag(FName("Action.InAir.Attack.Attacking"), ActionTagSet.ActionAirAttacking);


    AddTag(FName("Action.Stand.Skill"), ActionTagSet.SkillActionParent);
    AddTag(FName("Action.Stand.Skill.Slide"), ActionTagSet.ActionSlide);
    AddTag(FName("Action.Stand.Skill.Avoid"), ActionTagSet.ActionAvoid);
    AddTag(FName("Action.Stand.Skill.Dodge"), ActionTagSet.ActionDodge);

    AddTag(FName("Action.Stand.Skill.Skill1"), ActionTagSet.ActionSkill1);
    AddTag(FName("Action.Stand.Skill.Skill2"), ActionTagSet.ActionSkill2);
    AddTag(FName("Action.Stand.Skill.Skill3"), ActionTagSet.ActionSkill3);
    AddTag(FName("Action.Stand.Skill.Skill4"), ActionTagSet.ActionSkill4);
    AddTag(FName("Action.Stand.Skill.Skill5"), ActionTagSet.ActionSkill5);
    AddTag(FName("Action.Stand.Skill.Ulti"), ActionTagSet.ActionUlti);


    
    AddTag(FName("ItemSlot"), ItemSlotTagSet.SlotParent);
    AddTag(FName("ItemSlot.Weapon"), ItemSlotTagSet.SlotWeapon);


    AddTag(FName("Character"), CharacterTagSet.CharacterParent);
    AddTag(FName("Character.Player"), CharacterTagSet.PlayerTag);
    AddTag(FName("Character.Monster"), CharacterTagSet.MonsterTag);


    AddTag(FName("Control.Player"), EquipPlayerParent);
    AddTag(FName("Control.AI"), EquipAIParent);

    AddTag(FName("Action.Stand"), ActionLocationTagSet.StandActionTag);
    AddTag(FName("Action.Down"), ActionLocationTagSet.DownActionTag);
    AddTag(FName("Action.InAir"), ActionLocationTagSet.InAirActionTag);


    AddContainerTag(FName("Action.Stand.Damaged.Dead"), DeadContainer);
    AddContainerTag(FName("Action.Down.Damaged.Dead"), DeadContainer);
    AddContainerTag(FName("Action.InAir.Damaged.Dead"), DeadContainer);


    AddTag(FName("Damaged.KeepDown"), HitTagSet.DamagedDown);
    AddTag(FName("Damaged.Standing"), HitTagSet.DamagedStanding);

    AddTag(FName("Damaged.Hit"), HitTagSet.DamagedNormal);
    AddTag(FName("Damaged.AirLaunch"), HitTagSet.DamagedAirLaunch);
    AddTag(FName("Damaged.InAir"), HitTagSet.DamagedInAir);


    AddTag(FName("Damaged.LargeHit"), HitTagSet.DamagedLarge);
    AddTag(FName("Damaged.CriticalHit"), HitTagSet.DamagedCritical);
    AddTag(FName("Damaged.Dead"), HitTagSet.DamagedDead);


    AddContainerTag(FName("Action.Stand.Damaged"), DamagedParentContainer);
    AddContainerTag(FName("Action.Down.Damaged"), DamagedParentContainer);
    AddContainerTag(FName("Action.InAir.Damaged"), DamagedParentContainer);
    
}

void UHyTagSubsystem::AddTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);
}

void UHyTagSubsystem::AddContainerTag(const FName& InTagName, FGameplayTagContainer& InTagContainer)
{
	InTagContainer.AddTag(FGameplayTag::RequestGameplayTag(InTagName));


}


const bool UHyTagSubsystem::IsNormalAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.NorActionParent))
    {
        return true;
    }

    if (InActionTag.MatchesTag(ActionTagSet.NorAirActionParent))
    {
        return true;
    }
    
    return false;
}

const bool UHyTagSubsystem::IsDoingAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.DoingActionParent))
    {
        return true;
    }

    return false;
}

const bool UHyTagSubsystem::IsJumpAction(const FGameplayTag& InActionTag) const
{
    return ActionTagSet.ActionJump == InActionTag;
}

const bool UHyTagSubsystem::IsMoveAction(const FGameplayTag& InActionTag) const
{
    return ActionTagSet.ActionMove == InActionTag;
}

const bool UHyTagSubsystem::IsSkillAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.SkillActionParent))
    {
        return true;
    }
    return false;
}

const bool UHyTagSubsystem::IsDodgeAction(const FGameplayTag& InActionTag) const
{
    // TODO 임시 회피
    if (InActionTag == ActionTagSet.ActionDodge)
    {
        return true;
    }


    return false;
}

const bool UHyTagSubsystem::IsAttackAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.AttActionParent))
    {
        return true;
    }

    if (InActionTag.MatchesTag(ActionTagSet.ActionAirAttackParent))
    {
        return true;
    }

    return false;
}

const bool UHyTagSubsystem::IsComboAttackAction(const FGameplayTag& InActionTag) const
{
    return ActionTagSet.ActionAttack == InActionTag;
}

const bool UHyTagSubsystem::IsDashAttackAction(const FGameplayTag& InActionTag) const
{
    return ActionTagSet.ActionDashAttack == InActionTag;
}

const bool UHyTagSubsystem::IsChargeAttackAction(const FGameplayTag& InActionTag) const
{
    return ActionTagSet.ActionChargeAttack == InActionTag;
}

const bool UHyTagSubsystem::IsDeadAction(const FGameplayTag& InActionTag) const
{
    return DeadContainer.HasTag(InActionTag);
}

const bool UHyTagSubsystem::IsStandAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionLocationTagSet.StandActionTag))
    {
        return true;
    }

    return false;
}

const bool UHyTagSubsystem::IsDownAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionLocationTagSet.DownActionTag))
    {

        return true;
    }

    return false;
}

const bool UHyTagSubsystem::IsInAirAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionLocationTagSet.InAirActionTag))
    {
        return true;
    }


    return false;
}

const bool UHyTagSubsystem::IsDamagedAction(const FGameplayTag& InActionTag) const
{
    for (const FGameplayTag& Tag : DamagedParentContainer)
    {
        if (InActionTag.MatchesTag(Tag))
        {
            return true;
        }
    }
 
    return false;
}

const FGameplayTag UHyTagSubsystem::GetActionTypeByDamageType(const FGameplayTag& InDamageType, const FGameplayTag& CurActionTag) const
{
    // HitTag와 현재 base Action으로 HitAction Tag를 만드는 함수
    // Action.Stand + Damaged.Hit = Action.Stand.Damaged.Hit

    FGameplayTag HitActionTag = FGameplayTag::EmptyTag;
    if (IsStandAction(CurActionTag))
    {
        FString TagString;
        // 예외상황 AirLaunch이면 Stand > Air로
        if (InDamageType == HitTagSet.DamagedAirLaunch)
        {
            TagString = ActionLocationTagSet.InAirActionTag.ToString() + "." + InDamageType.ToString();
        }
        else
        {
            TagString = ActionLocationTagSet.StandActionTag.ToString() + "." + InDamageType.ToString();
        }

        HitActionTag = FGameplayTag::RequestGameplayTag(FName(*TagString));
    }
	else if (IsDownAction(CurActionTag))
	{
        // 예외상황 AirLaunch이면 Stand > Air로
        FString TagString;
        if (InDamageType == HitTagSet.DamagedAirLaunch)
        {
            TagString = ActionLocationTagSet.InAirActionTag.ToString() + "." + InDamageType.ToString();
        }
        else
        {
            TagString = ActionLocationTagSet.DownActionTag.ToString() + "." + InDamageType.ToString();
        }
	}
	else if (IsInAirAction(CurActionTag))
	{
        FString TagString = ActionLocationTagSet.InAirActionTag.ToString() + "." + InDamageType.ToString();
        HitActionTag = FGameplayTag::RequestGameplayTag(FName(*TagString));

	}

    return HitActionTag;
}

const bool UHyTagSubsystem::IsNormalHit(const FGameplayTag& InDamageType) const
{
    return HitTagSet.DamagedNormal == InDamageType;
}

const bool UHyTagSubsystem::IsLargeHit(const FGameplayTag& InDamageType) const
{
    return HitTagSet.DamagedLarge == InDamageType;
}

const bool UHyTagSubsystem::IsCriticalHit(const FGameplayTag& InDamageType) const
{
    return HitTagSet.DamagedCritical == InDamageType;
}

const bool UHyTagSubsystem::IsPlayerCharacter(const FGameplayTag& InCharacterTag) const
{
    return CharacterTagSet.PlayerTag == InCharacterTag;
}

const bool UHyTagSubsystem::IsMonsterCharacter(const FGameplayTag& InCharacterTag) const
{
    return CharacterTagSet.MonsterTag == InCharacterTag;
}

const bool UHyTagSubsystem::IsUserPlaying(const FGameplayTag& InEquipTag) const
{
    return InEquipTag.MatchesTag(EquipPlayerParent);

}

const bool UHyTagSubsystem::IsAIPlaying(const FGameplayTag& InEquipTag) const
{
    return InEquipTag.MatchesTag(EquipAIParent);
}
