#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableTypes.h"

#include "SpawnInfo_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct HYTABLE_API FSpawnInfo_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FSpawnInfo_TableEntity()
	{
		SpawnInfoID = 0;
		HomeLocation = FVector::ZeroVector;
		HomeRange = 0.0f;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	int32 SpawnInfoID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FVector HomeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	float HomeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	TArray<FVector> PatrolPoints;
};
