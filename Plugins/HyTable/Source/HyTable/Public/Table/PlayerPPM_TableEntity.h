#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableTypes.h"

#include "PlayerPPM_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct HYTABLE_API FPlayerPPM_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FPlayerPPM_TableEntity()
	{
		PPMID = 0;
		PPMPath = "";
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	int32 PPMID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FString PPMPath;
};
