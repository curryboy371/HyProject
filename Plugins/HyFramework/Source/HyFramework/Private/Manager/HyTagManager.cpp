// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HyTagManager.h"

void UHyTagManager::InitManager()
{
    InitTagSet();


}

void UHyTagManager::ReleaseManager()
{

}

void UHyTagManager::InitTagSet()
{
    AddActionTag(FName("Action.Stand.Normal"), ActionExcuteSet.NorActionParent);
    AddActionTag(FName("Action.Stand.Normal.Spawn"), ActionExcuteSet.ActionSpawn, EActionPriority::ENone);
    AddActionTag(FName("Action.Stand.Normal.Idle"), ActionExcuteSet.ActionIdle, EActionPriority::ENone);
    AddActionTag(FName("Action.Stand.Normal.Move"), ActionExcuteSet.ActionMove, EActionPriority::ELow);

    AddActionTag(FName("Action.Stand.Doing"), ActionExcuteSet.DoingActionParent);
    AddActionTag(FName("Action.Stand.Doing.Jump"), ActionExcuteSet.ActionJump, EActionPriority::EMedium);
    AddActionTag(FName("Action.Stand.Doing.Equip"), ActionExcuteSet.ActionEquip, EActionPriority::EMedium);
    AddActionTag(FName("Action.Stand.Doing.UnEquip"), ActionExcuteSet.ActionUnEquip, EActionPriority::EMedium);
    AddActionTag(FName("Action.Stand.Doing.Crouching"), ActionExcuteSet.ActionCrouching, EActionPriority::EMedium);

    AddActionTag(FName("Action.Stand.Attack"), ActionExcuteSet.AttActionParent);
    AddActionTag(FName("Action.Stand.Attack.Attacking"), ActionExcuteSet.ActionAttack, EActionPriority::EMedium);




    AddOtherTag(FName("ItemSlot"), ItemSlotTagSet.SlotParent);
    AddOtherTag(FName("ItemSlot.Weapon"), ItemSlotTagSet.SlotWeapon);
}

void UHyTagManager::AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);

}

void UHyTagManager::AddActionTag(const FName& InTagName, FActionExcuteData& InActionExcuteData, EActionPriority InActionProperty)
{
	InActionExcuteData.TagName = FGameplayTag::RequestGameplayTag(InTagName);
	InActionExcuteData.ActionPriority = InActionProperty;
}

void UHyTagManager::AddOtherTag(const FName& InTagName, FGameplayTag& InTagInst)
{
	InTagInst = FGameplayTag::RequestGameplayTag(InTagName);
}

void UHyTagManager::AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple)
{
}

const bool UHyTagManager::IsNormalAction(FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionExcuteSet.NorActionParent))
    {
        return true;
    }

    return false;
}

const bool UHyTagManager::IsDoingAction(FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionExcuteSet.DoingActionParent))
    {
        return true;
    }

    return false;
}

const bool UHyTagManager::IsAttackAction(FGameplayTag& InActionTag)
{
    if (InActionTag.MatchesTag(ActionExcuteSet.AttActionParent))
    {
        return true;
    }
    return false;
}
