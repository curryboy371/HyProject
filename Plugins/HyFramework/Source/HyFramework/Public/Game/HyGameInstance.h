// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CControlTypes.h"

#include "GameplayTagContainer.h"

#include "HyGameInstance.generated.h"

/**
 * 
 */

typedef UHyGameInstance UHyInst;

UCLASS()
class HYFRAMEWORK_API UHyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
// Manager
	void InitManager();
	void ReleaseManager();


#pragma region ExecCommand
	UFUNCTION(Exec)
	void ExecTestCommand(const int32 InTestID);

	UFUNCTION(Exec)
	void ExecSpawnMonsterCommand(const int32 InMonsterID);

	UFUNCTION(Exec)
	void ExecSpawnPlayerCommand(const int32 InPlayerID);

#pragma endregion


	template<typename T>
	T* GetManager()
	{
		static_assert(TIsDerivedFrom<T, UHyManagerBase>::Value, "T must be derived from UHyManagerBase");
		
		uint8 FindManagerID = T::StaticClass()->GetDefaultObject<T>()->GetManagerID();
		UHyManagerBase** FindManager = HyManagerMap.Find(FindManagerID);
		if (FindManager && *FindManager)
		{
			// TODO Casting을 피할 수 있는 방법에 대해 고민
			return Cast<T>(*FindManager);
		}

		return nullptr;
	}

public:
	static UHyGameInstance* Get()
	{
		if (HyGameInstance) { return HyGameInstance; }
		else { HyGameInstance = Cast<UHyGameInstance>(GWorld->GetGameInstance());}
		if (HyGameInstance) { return HyGameInstance;}

		return HyGameInstance;
	}


	static UHyGameInstance* HyGameInstance;

	const bool GetInputDataSet(const FGameplayTag& InInputTag, FInputDataSet& OutInputData);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	TArray<FInputDataSet> InputDataSet;


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hy | Manager")
	TMap<uint8, class UHyManagerBase*> HyManagerMap;
};
