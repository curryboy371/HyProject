#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableTypes.h"

#include "Player_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct HYTABLE_API FPlayer_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FPlayer_TableEntity()
	{
		PlayerID = 0;
		PlayerName = PlayerName = "";
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	int32 PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName PlayerPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName PlayerName;
};
