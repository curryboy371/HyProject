// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HyGameInstance.h"

#include "Manager/HyManagerBase.h"

#include "HyCoreLogging.h"

UHyGameInstance* UHyGameInstance::HyGameInstance = nullptr;

void UHyGameInstance::Init()
{
	UGameInstance::Init();
    HyGameInstance = nullptr;
    InitManager();
}

void UHyGameInstance::Shutdown()
{
    ReleaseManager();
    HyGameInstance = nullptr;
    UGameInstance::Shutdown();
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
