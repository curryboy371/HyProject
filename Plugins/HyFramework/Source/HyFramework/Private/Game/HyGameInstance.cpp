// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyGameInstance.h"

#include "Manager/HyManagerBase.h"
#include "Manager/HySpawnManager.h"

#include "HyCoreMacro.h"

#include "HyTagSubsystem.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

UHyGameInstance* UHyGameInstance::HyGameInstance = nullptr;

void UHyGameInstance::Init()
{
	UGameInstance::Init();

    // 메모리 누수 체크 활성화
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    HyGameInstance = nullptr;
    InitManager();
}

void UHyGameInstance::Shutdown()
{
    ReleaseManager();
    HyGameInstance = nullptr;
    UGameInstance::Shutdown();

    // 프로그램 종료 시 메모리 누수 확인
    _CrtDumpMemoryLeaks();
}

void UHyGameInstance::InitManager()
{
    UHyManagerBase::ResetManagerID();
    HyManagerMap.Empty();

    // 모든 UClass를 순회하며 UManagerBase를 상속하는 클래스를 찾음
    for (TObjectIterator<UClass> It; It; ++It)
    {
        UClass* Class = *It;

        if (Class->IsChildOf(UHyManagerBase::StaticClass()) && !Class->HasAnyClassFlags(CLASS_Abstract))
        {
            // 해당 클래스를 인스턴스화하여 Managers 배열에 추가
            UHyManagerBase* NewManager = NewObject<UHyManagerBase>(this, Class);
            if (NewManager)
            {
                if (HyManagerMap.Contains(NewManager->GetManagerID()) == false)
                {
                    HyManagerMap.Add(NewManager->GetManagerID(), NewManager);
                }
                else
                {
                    ERR_V("Manager ID %d is already exist", NewManager->GetManagerID());
                }
            }
        }
    }

    for (auto& manager : HyManagerMap)
    {
        manager.Value->InitManager();
    }
}

void UHyGameInstance::ReleaseManager()
{
	for (auto& manager : HyManagerMap)
	{
		manager.Value->ReleaseManager();
	}

    UHyManagerBase::ResetManagerID();
	HyManagerMap.Empty();
}

void UHyGameInstance::ExecTestCommand(const int32 InTestID)
{
    WAR_V("(%d)", InTestID);
}

void UHyGameInstance::ExecSpawnMonsterCommand(const int32 InMonsterID, const int32 InSpawnID/* = 0*/)
{
	UHySpawnManager* SpawnManager = GetManager<UHySpawnManager>();
	if(SpawnManager)
	{
		SpawnManager->SpawnCharacter(InMonsterID, InSpawnID, GET_TAG_SUBSYSTEM()->CharacterTagSet.MonsterTag);
	}
    else
    {
        ERR_V("SpawnManager is nullptr");
    }
}

void UHyGameInstance::ExecSpawnPlayerCommand(const int32 InPlayerID, const int32 InSpawnID/* = 0*/)
{
    UHySpawnManager* SpawnManager = GetManager<UHySpawnManager>();
    if (SpawnManager)
    {
        SpawnManager->SpawnCharacter(InPlayerID, InSpawnID, GET_TAG_SUBSYSTEM()->CharacterTagSet.PlayerTag);
    }
    else
    {
        ERR_V("SpawnManager is nullptr");
    }
}

const bool UHyGameInstance::GetInputDataSet(const FGameplayTag& InInputTag, FInputDataSet& OutInputData)
{
	for (const FInputDataSet& InputData : InputDataSet)
	{
		if (InputData.TagName == InInputTag)
		{
			OutInputData = InputData;
			return true;
		}
	}

	ERR_V("Invalid Input Tag %s", *InInputTag.ToString());
	return false;
}
