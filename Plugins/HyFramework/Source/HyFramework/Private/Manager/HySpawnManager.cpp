// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HySpawnManager.h"

#include "Actors/Character/HyMyPlayerBase.h"
#include "Actors/Character/HyMonsterBase.h"

#include "HyCoreMacro.h"


UHySpawnManager::UHySpawnManager()
{
	LocalPlayer = nullptr;
}

void UHySpawnManager::InitManager()
{
	LocalPlayer = nullptr;

	SpawnedPlayerMap.Reset();
	SpawnedCharacterMap.Reset();
	SpawnedMonsterMap.Reset();
}

void UHySpawnManager::ReleaseManager()
{
	LocalPlayer = nullptr;

	SpawnedPlayerMap.Reset();
	SpawnedCharacterMap.Reset();
	SpawnedMonsterMap.Reset();
}

void UHySpawnManager::SetLocalPlayer(TObjectPtr<class AHyMyPlayerBase> InLocalPlayer)
{
	if (!InLocalPlayer)
	{
		ERR_V("InLocalPlayer is nullptr");
		return;
	}

	if (LocalPlayer)
	{
		FGuid& PlayerGuid = LocalPlayer->GetMyGuidRef();
		if (PlayerGuid.IsValid() == false)
		{
			ERR_V("PlayerGuid is invalid");
			return;
		}

		if (SpawnedPlayerMap.Contains(PlayerGuid))
		{
			ERR_V("PlayerGuid is already exist");
			return;
		}

	}
	else
	{
		LocalPlayer = InLocalPlayer;
		SpawnedPlayerMap.Add(LocalPlayer->GetMyGuidRef(), LocalPlayer);
	}




}
