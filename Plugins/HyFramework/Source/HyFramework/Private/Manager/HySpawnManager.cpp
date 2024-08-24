// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/HySpawnManager.h"

#include "Actors/Character/HyMyPlayerBase.h"
#include "Actors/Character/HyMonsterBase.h"


#include "Game/HyGameInstance.h"

#include "Game/HyPlayerController.h"

#include "HyTableSubsystem.h"
#include "Table/Monster_TableEntity.h"
#include "Table/Player_TableEntity.h"

#include "Game/HyPlayerController.h"

#include "HyTagSubsystem.h"

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
		if (!Monster.Value)
		{
			continue;
		}

		if(IsValidMonster(Monster.Key) == false)
		{
			continue;
		}

		FVector TargetDir = Monster.Value->GetActorLocation() - InCompareLocation;
		float TargetDistance = TargetDir.Size();
		if (InEnableLength > TargetDistance && ClosetDistance > TargetDistance)
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

void UHySpawnManager::SpawnCharacter(const int32 InCharacterID, const FGameplayTag& InCharacterTypeTag)
{
	if (InCharacterID <= 0)
	{
		ERR_V(TEXT("Invalid InCharacterID"));
		return;
	}

	UHyTagSubsystem* SubSystemTag = GET_TAG_SUBSYSTEM();
	if (!SubSystemTag)
	{
		ERR_V("SubSystemTag is nullptr");
		return;
	}

	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	AHyPlayerController* HyPC = Cast<AHyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (HyPC == nullptr)
	{
		ERR_V("invalid player controller");
		return;
	}

	FVector HitLocation;
	if (HyPC->GetMouseRaycastHitLocation(HitLocation) == false)
	{
		ERR_V("invalid mouse cursor location");
		return;
	}
	
	UHyTableSubsystem* TableSubSystem = Inst->GetSubsystem<UHyTableSubsystem>();
	if (!TableSubSystem)
	{
		ERR_V("TableSubSystem is not set.");
		return;
	}


	if (SubSystemTag->IsPlayerCharacter(InCharacterTypeTag))
	{
		FPlayer_TableEntity* PlayerEntity = TableSubSystem->GetTableData<FPlayer_TableEntity>(InCharacterID);
		if (!PlayerEntity)
		{
			ERR_V("PlayerEntity is not set. ID=%d", InCharacterID);
		}

		HitLocation.Z += 10.f;
		FResourceloaderArgument* pArg = new FResourceloaderArgument(PlayerEntity->PlayerID, EGenerateType::EGen_Character, HitLocation, FRotator::ZeroRotator);
		if (OnSpawCharacter(PlayerEntity->PlayerPath, pArg) == false)
		{
			// Success시 delete는 SpawnComplete에서
			if (pArg)
			{
				delete pArg;
				pArg = nullptr;
			}
		}
	}
	else if (SubSystemTag->IsMonsterCharacter(InCharacterTypeTag))
	{
		FMonster_TableEntity* MonsterEntity = TableSubSystem->GetTableData<FMonster_TableEntity>(InCharacterID);
		if (!MonsterEntity)
		{
			ERR_V("MonsterEntity is not set. ID=%d", InCharacterID);

		}

		HitLocation.Z += 10.f;
		FResourceloaderArgument* pArg = new FResourceloaderArgument(MonsterEntity->MonsterID, EGenerateType::EGen_Character, HitLocation, FRotator::ZeroRotator);
		if (OnSpawCharacter(MonsterEntity->MonsterPath, pArg) == false)
		{
			// Success시 delete는 SpawnComplete에서
			if (pArg)
			{
				delete pArg;
				pArg = nullptr;
			}
		}
	}



}

const bool UHySpawnManager::OnSpawCharacter(const FName& InCharacterPath, FResourceloaderArgument* pArg)
{
	if(!pArg)
	{
		ERR_V("pArg is nullptr");
		return false;
	}

	if (pArg->ObjectID <= 0)
	{
		ERR_V("Invalid ObjectID");
		return false;
	}

	if (InCharacterPath == NAME_None)
	{
		ERR_V("InCharacterPath is Name None");
		return false;
	}

	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("HyInst is not set.");
		return false;
	}

	UHyResourceLoadSubsystem* ResourceLoadSubsystem = Inst->GetSubsystem<UHyResourceLoadSubsystem>();
	if (!ResourceLoadSubsystem)
	{
		ERR_V("ResourceLoadSubsystem is not set.");
		return false;
	}

	// Object AsyncLoad Start
	ResourceLoadSubsystem->LoadMemoryAsync(InCharacterPath, pArg, FResourceLoaderAsyncDelegate::CreateUObject(this, &UHySpawnManager::OnGenerateObject));
	return true;
}

void UHySpawnManager::OnGenerateObject(FResourceloaderArgument* pArg)
{
	// Object AsyncLoad End
	if (CheckResourceLoaderArg(pArg) == false)
	{
		if (pArg)
		{
			delete pArg;
			pArg = nullptr;
		}
		ERR_V("CheckResourceLoaderArg");
		return;
	}

	pArg->Location.Z += 100.f;
	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(Cast<UClass>(pArg->GetObjectPtr()), pArg->Location, pArg->Rotation);
	if (!SpawnActor)
	{
		ERR_V("Spawn Actor is nullptr");
		pArg->bIsError = true;
	}

	SpawnComplete(SpawnActor, pArg->bIsError, pArg);
}

const bool UHySpawnManager::CheckResourceLoaderArg(FResourceloaderArgument* pArg)
{
	if (!pArg)
	{
		ERR_V("pArg is nullptr");
		return false;
	}

	if (pArg->bIsError)
	{
		ERR_V("bIsError");
		return false;
	}

	if (pArg->ObjectID <= 0)
	{
		ERR_V("Invalid ObjectID");
		pArg->bIsError = true;
		return false;
	}

	if (pArg->GenType == EGenerateType::EGen_None)
	{
		ERR_V("Invalid GenerateType");
		pArg->bIsError = true;
		return false;
	}

	if (!pArg->GetObjectPtr())
	{
		ERR_V("ObjectPtr is Null");
		return false;
	}


	return true;
}

void UHySpawnManager::SpawnComplete(TObjectPtr<AActor> InSpawnActor, bool bError, FResourceloaderArgument* pArg)
{
	// Object AsyncLoad Completed

	if (CheckResourceLoaderArg(pArg) == false)
	{
		if (pArg)
		{
			delete pArg;
			pArg = nullptr;
		}
		ERR_V("CheckResourceLoaderArg");
		return;
	}

	if (!InSpawnActor)
	{
		ERR_V("InSpawnActor is nullptr");
		pArg->bIsError = true;
	}

	if (pArg->bIsError)
	{
		ERR_V("bIsError");
	}
	else
	{
		bool bSpawnComplete = false;

		switch (pArg->GenType)
		{
			case EGenerateType::EGen_Character:
			{
				if (InSpawnActor->IsA<AHyPlayerBase>())
				{
					if (AHyPlayerBase* Player = Cast<AHyPlayerBase>(InSpawnActor))
					{
						Player->SpawnCompleted();

						SpawnedPlayerMap.Add(Player->GetMyGuidRef(), Player);
						SpawnedCharacterMap.Add(Player->GetMyGuidRef(), Player);
						bSpawnComplete = true;
					}
				}
				else if (InSpawnActor->IsA<AHyMonsterBase>())
				{
					if (AHyMonsterBase* Monster = Cast<AHyMonsterBase>(InSpawnActor))
					{
						Monster->SpawnCompleted();
						SpawnedMonsterMap.Add(Monster->GetMyGuidRef(), Monster);
						SpawnedCharacterMap.Add(Monster->GetMyGuidRef(), Monster);
						bSpawnComplete = true;
					}
				}
			}
		}
	}

	if (pArg != nullptr)
	{
		delete pArg;
	}
}
