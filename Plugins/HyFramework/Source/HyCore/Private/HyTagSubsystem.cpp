// Fill out your copyright notice in the Description page of Project Settings.


#include "HyTagSubsystem.h"

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

    AddTag(FName("Action.Stand.Doing"), ActionTagSet.DoingActionParent);
    AddTag(FName("Action.Stand.Doing.Jump"), ActionTagSet.ActionJump);
    AddTag(FName("Action.Stand.Doing.Equip"), ActionTagSet.ActionEquip);
    AddTag(FName("Action.Stand.Doing.UnEquip"), ActionTagSet.ActionUnEquip);
    AddTag(FName("Action.Stand.Doing.Crouching"), ActionTagSet.ActionCrouching);

    AddTag(FName("Action.Stand.Attack"), ActionTagSet.AttActionParent);
    AddTag(FName("Action.Stand.Attack.Attacking"), ActionTagSet.ActionAttack);



    AddTag(FName("ItemSlot"), ItemSlotTagSet.SlotParent);
    AddTag(FName("ItemSlot.Weapon"), ItemSlotTagSet.SlotWeapon);


    AddTag(FName("Character"), CharacterTagSet.CharacterParent);
    AddTag(FName("Character.Player"), CharacterTagSet.PlayerTag);
    AddTag(FName("Character.Monster"), CharacterTagSet.MonsterTag);


    AddTag(FName("Player"), EquipPlayerParent);
    AddTag(FName("AI"), EquipAIParent);

}

void UHyTagSubsystem::AddTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);
}

void UHyTagSubsystem::AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple)
{
}

const bool UHyTagSubsystem::IsNormalAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.NorActionParent))
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

const bool UHyTagSubsystem::IsAttackAction(const FGameplayTag& InActionTag) const
{
    if (InActionTag.MatchesTag(ActionTagSet.AttActionParent))
    {
        return true;
    }
    return false;
}

const bool UHyTagSubsystem::IsDeadAction(const FGameplayTag& InActionTag) const
{
    return DeadContainer.HasTag(InActionTag);
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
