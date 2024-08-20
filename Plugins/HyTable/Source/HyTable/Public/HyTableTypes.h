// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Engine/DataTable.h"
#include "UObject/Object.h"

#include "HyTableTypes.generated.h"


// HyTable base struct
USTRUCT(BlueprintType)
struct HYTABLE_API FHyTableRowBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

};




UCLASS()
class HYTABLE_API UHyDataTable : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy|DataTable")
	UDataTable* DataTable;
};


/**
 * 
 */
UCLASS()
class HYTABLE_API UHyTableTypes : public UObject
{
	GENERATED_BODY()
	
};
