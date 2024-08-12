#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableRowBase.h"
#include "TriggerInfo_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct FTriggerInfo
{
	GENERATED_BODY()

	FTriggerInfo()
	{
		SpawnID = 0;
		SpawnLocation = FVector::ZeroVector;
		SpawnRotator = FRotator::ZeroRotator;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	int32 SpawnID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	FRotator SpawnRotator;

};

USTRUCT(BlueprintType)
struct HYTABLE_API FTriggerInfo_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FTriggerInfo_TableEntity()
	{
		TriggerID = 0;
		TriggerInfos.Reset();
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	int32 TriggerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trigger)
	TArray<FTriggerInfo> TriggerInfos; // TODO csv로 만들면 array 풀어야함
};
