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

const FGameplayTag UHySpawnManager::GetCharacterAction(const FGuid& InCharacterGuid)
{

	return FGameplayTag();
}

const bool UHySpawnManager::IsValidCharacter(const FGuid& InCharacterGuid, bool bIncludeDeadCharacter)
{
	if (InCharacterGuid.IsValid() == false)
	{
		ERR_V("Invalid Character Guid");
		return false;
	}

	if (TObjectPtr<class AHyCharacterBase>* FindCharacter = SpawnedCharacterMap.Find(InCharacterGuid))
	{
		if (*FindCharacter)
		{

			if ((*FindCharacter)->IsDead())
			{
				if (!bIncludeDeadCharacter)
				{
					ERR_V("Character is dead %s", *InCharacterGuid.ToString());
					return false;
				}
			}
			else
			{
				return true;
			}
		}
	}

	ERR_V("Character is not exist %s", *InCharacterGuid.ToString());
	return false;
}

const bool UHySpawnManager::IsValidMonster(const FGuid& InMonsterGuid)
{
	if (InMonsterGuid.IsValid() == false)
	{
		ERR_V("Invalid Monster Guid");
		return false;
	}

	if (TObjectPtr<class AHyMonsterBase>* FindMonster = SpawnedMonsterMap.Find(InMonsterGuid))
	{
		if (*FindMonster)
		{
			if ((*FindMonster)->IsDead())
			{
				ERR_V("Monster is dead %s", *InMonsterGuid.ToString());
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	ERR_V("Monster is not exist %s", *InMonsterGuid.ToString());
	return false;
}

const bool UHySpawnManager::IsValidPlayer(const FGuid& InPlayerGuid)
{
	if (InPlayerGuid.IsValid() == false)
	{
		ERR_V("Invalid Player Guid");
		return false;
	}

	if (TObjectPtr<class AHyPlayerBase>* FindPlayer = SpawnedPlayerMap.Find(InPlayerGuid))
	{
		if (*FindPlayer)
		{
			if ((*FindPlayer)->IsDead())
			{
				ERR_V("Player is dead %s", *InPlayerGuid.ToString());
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	ERR_V("Player is not exist %s", *InPlayerGuid.ToString());
	return false;
}

TObjectPtr<class AHyCharacterBase> UHySpawnManager::GetCharacterByGuid(const FGuid& InCharacterGuid)
{
	if (IsValidCharacter(InCharacterGuid), false)
	{
		return nullptr;
	}

	return SpawnedCharacterMap[InCharacterGuid];
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

const bool UHySpawnManager::FindTargetMonster(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid)
{
	bool bFindTarget = false;
	float ClosetDistance = 1000000.f;

	OutTargetGuid.Invalidate();
	
	for(auto& Monster : SpawnedMonsterMap)
	{
		if (Monster.Value)
		{
			continue;
		}

		if(IsValidMonster(Monster.Key) == false)
		{
			continue;
		}

		FVector TargetDir = Monster.Value->GetActorLocation() - InCompareLocation;
		float TargetDistance = TargetDir.Size();
		if (InEnableLength < TargetDistance && ClosetDistance > TargetDistance)
		{
			ClosetDistance = InEnableLength;
			OutTargetGuid = Monster.Key;
			bFindTarget = true;
		}
	}

	return bFindTarget;
}

const bool UHySpawnManager::FindTargetPlayer(const FVector& InCompareLocation, const float InEnableLength, FGuid& OutTargetGuid)
{

	return false;
}
