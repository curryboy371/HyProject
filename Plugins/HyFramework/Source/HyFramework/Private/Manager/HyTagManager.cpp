// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HyTagManager.h"

void UHyTagManager::InitManager()
{
	InitActionTagSet();
}

void UHyTagManager::ReleaseManager()
{

}

void UHyTagManager::InitActionTagSet()
{
    AddActionTag(FName("Action.Stand.Normal"), ActionExcuteSet.NorActionParent);
    AddActionTag(FName("Action.Stand.Normal.Spawn"), ActionExcuteSet.ActionSpawn, EActionPriority::ENone);
    AddActionTag(FName("Action.Stand.Normal.Idle"), ActionExcuteSet.ActionIdle, EActionPriority::ENone);
    AddActionTag(FName("Action.Stand.Normal.Walk"), ActionExcuteSet.ActionWalk, EActionPriority::ELow);
    AddActionTag(FName("Action.Stand.Normal.Run"), ActionExcuteSet.ActionRun, EActionPriority::ELow);
    AddActionTag(FName("Action.Stand.Normal.Jump"), ActionExcuteSet.ActionJump, EActionPriority::EMedium);
    AddActionTag(FName("Action.Stand.Normal.Equip"), ActionExcuteSet.ActionEquip, EActionPriority::EMedium);
    AddActionTag(FName("Action.Stand.Normal.UnEquip"), ActionExcuteSet.ActionUnEquip, EActionPriority::EMedium);

    AddActionTag(FName("Action.Stand.Attack"), ActionExcuteSet.AttActionParent);
    AddActionTag(FName("Action.Stand.Attack.Attacking"), ActionExcuteSet.ActionAttack, EActionPriority::EMedium);
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

void UHyTagManager::AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst, EActionPriority InActionProperty)
{
}

void UHyTagManager::AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple, EActionPriority InActionProperty)
{
}
