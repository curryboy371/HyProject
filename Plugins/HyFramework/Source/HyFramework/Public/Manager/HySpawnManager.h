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
	//void SpawnCharacter(const FGuid& InGuid, const FGameplayTag& InTag, const FVector& InLocation, const FRotator& InRotation);

	TObjectPtr<class AHyMyPlayerBase> GetLocalPlayer() { return LocalPlayer; }
	void SetLocalPlayer(TObjectPtr<class AHyMyPlayerBase> InLocalPlayer);

protected:
	TMap<FGuid, TObjectPtr<class AHyCharacter>> SpawnedCharacterMap;
	TMap<FGuid, TObjectPtr<class AHyPlayerBase>> SpawnedPlayerMap;
	TMap<FGuid, TObjectPtr<class AHyMonsterBase>> SpawnedMonsterMap;

	TObjectPtr<class AHyMyPlayerBase> LocalPlayer;
};
