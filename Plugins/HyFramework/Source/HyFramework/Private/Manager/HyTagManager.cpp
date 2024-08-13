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
    AddActionTag(FName("Action.Stand.Normal"), NorActionTagSet.ActionParent);
    AddActionTag(FName("Action.Stand.Normal.Spawn"), NorActionTagSet.ActionSpawn);
    AddActionTag(FName("Action.Stand.Normal.Idle"), NorActionTagSet.ActionIdle);
    AddActionTag(FName("Action.Stand.Normal.Walk"), NorActionTagSet.ActionWalk);
    AddActionTag(FName("Action.Stand.Normal.Run"), NorActionTagSet.ActionRun);
    AddActionTag(FName("Action.Stand.Normal.Jump"), NorActionTagSet.ActionJump);
    AddActionTag(FName("Action.Stand.Normal.Equip"), NorActionTagSet.ActionEquip);
    AddActionTag(FName("Action.Stand.Normal.UnEquip"), NorActionTagSet.ActionUnEquip);

    AddActionTag(FName("Action.Stand.Attack"), AttActionTagSet.ActionParent);
    AddActionTag(FName("Action.Stand.Attack.Attacking"), AttActionTagSet.ActionAttack);
}

void UHyTagManager::AddActionTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
    InActionTagInst = FGameplayTag::RequestGameplayTag(InTagName);
}

void UHyTagManager::AddOtherTag(const FName& InTagName, FGameplayTag& InActionTagInst)
{
}

void UHyTagManager::AddContainerTag(const FName& InTagName, FGameplayTuple& InTagTuple)
{
}
