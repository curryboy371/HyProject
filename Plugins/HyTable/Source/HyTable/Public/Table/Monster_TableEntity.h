#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableTypes.h"

#include "Monster_TableEntity.generated.h"

USTRUCT(BlueprintType)
struct HYTABLE_API FMonster_TableEntity : public FHyTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FMonster_TableEntity()
	{
		MonsterID = 0;
		MonsterName = MonsterPath = "";
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	int32 MonsterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName MonsterPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HyTable)
	FName MonsterName;
};
