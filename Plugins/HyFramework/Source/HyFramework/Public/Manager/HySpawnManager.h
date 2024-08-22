// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"
#include "GameplayTagContainer.h"

#include "HySpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHySpawnManager : public UHyManagerBase
{
	GENERATED_BODY()
	

public:
	UHySpawnManager();

	// UHyManagerBase을(를) 통해 상속됨
	virtual void InitManager();
	virtual void ReleaseManager();

public:
	const FGameplayTag GetCharacterAction(const FGuid& InCharacterGuid);

	const bool IsValidCharacter(const FGuid& InCharacterGuid, bool bIncludeDeadCharacter = false);
	const bool IsValidMonster(const FGuid& InMonsterGuid);
	const bool IsValidPlayer(const FGuid& InPlayerGuid);

	TObjectPtr<class AHyCharacterBase> GetCharacterByGuid(const FGuid& InCharacterGuid);

	TObjectPtr<class AHyMyPlayerBase> GetLocalPlayer() { return LocalPlayer; }
	void SetLocalPlayer(TObjectPtr<class AHyMyPlayerBase> InLocalPlayer);


public:
	const bool FindTargetMonster(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid);
	const bool FindTargetPlayer(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid);

protected:
	TMap<FGuid, TObjectPtr<class AHyCharacterBase>> SpawnedCharacterMap;
	TMap<FGuid, TObjectPtr<class AHyPlayerBase>> SpawnedPlayerMap;
	TMap<FGuid, TObjectPtr<class AHyMonsterBase>> SpawnedMonsterMap;

	TObjectPtr<class AHyMyPlayerBase> LocalPlayer;
};
