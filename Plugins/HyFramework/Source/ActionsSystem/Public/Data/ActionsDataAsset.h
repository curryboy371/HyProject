// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ActionsTypes.h"
#include "GameplayTagContainer.h"

#include "ActionsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONSSYSTEM_API UActionsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "TagName"), BlueprintReadWrite, Category = "Hy | Actions")
	TArray<FActionState> Actions;

public:
	void AddActionState(const FActionState& InActionState);

	bool GetActionByTag(const FGameplayTag& InActionTag, FActionState& OutActionState) const;

	void GetActions(TArray<FActionState>& OutActions) const 
	{
		OutActions = Actions;
	}
};
