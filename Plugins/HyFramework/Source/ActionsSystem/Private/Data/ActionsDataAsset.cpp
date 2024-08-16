// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ActionsDataAsset.h"

#include "HyCoreMacro.h"

void UActionsDataAsset::AddActionState(const FActionState& InActionState)
{
	// ActionState를 Actions에 추가, 이미 존재한다면 지우고 추가
	if (Actions.Contains(InActionState.TagName))
	{
		Actions.Remove(InActionState);
	}

	Actions.AddUnique(InActionState);
}

bool UActionsDataAsset::GetActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const
{
	// Action Tag로 Actions에서 ActionState를 반환받는 함수

	const FActionState* ActionState = Actions.FindByKey(InActionTag);
	if (ActionState)
	{
		OutActionState = *ActionState;
		return true;
	}

	return false;
}
