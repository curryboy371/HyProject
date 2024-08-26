// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/HyManagerBase.h"
#include "GameplayTagContainer.h"
#include "Resource/HyResourceLoadSubsystem.h"

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

	const bool IsValidCharacterWithLocation(const FGuid& InCharacterGuid, FVector& OutCharacterLocation);


	TObjectPtr<class AHyCharacterBase> GetCharacterByGuid(const FGuid& InCharacterGuid);

	TObjectPtr<class AHyMyPlayerBase> GetLocalPlayer() { return LocalPlayer; }
	void SetLocalPlayer(TObjectPtr<class AHyMyPlayerBase> InLocalPlayer);


public:
	const bool FindTargetMonster(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid, FVector& OutTargetLocation);
	const bool FindTargetPlayer(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid, FVector& OutTargetLocation);


public:
	void SpawnCharacter(const int32 InCharacterID, const int32 InSpawnID, const FGameplayTag& InCharacterTypeTag);

	const bool OnSpawCharacter(const FName& InCharacterPath, FResourceloaderArgument* pArg);

protected:
	void OnGenerateObject(FResourceloaderArgument* pArg);
	void SpawnComplete(TObjectPtr<AActor> InSpawnActor, bool bError, FResourceloaderArgument* pArg);

	const bool CheckResourceLoaderArg(FResourceloaderArgument* pArg);


protected:
	TMap<FGuid, TObjectPtr<class AHyCharacterBase>> SpawnedCharacterMap;
	TMap<FGuid, TObjectPtr<class AHyPlayerBase>> SpawnedPlayerMap;
	TMap<FGuid, TObjectPtr<class AHyMonsterBase>> SpawnedMonsterMap;

	TObjectPtr<class AHyMyPlayerBase> LocalPlayer;
};
