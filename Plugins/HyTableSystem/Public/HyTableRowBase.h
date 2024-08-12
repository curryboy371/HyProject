#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HyTableRowBase.generated.h"

// 프로젝트에서 생성된 구조체만 검색하기위해 base 분리.
USTRUCT(BlueprintType)
struct HYTABLE_API FHyTableRowBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
};