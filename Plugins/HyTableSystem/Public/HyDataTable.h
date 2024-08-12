// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HyDataTable.generated.h"

/**
 * 
 */
UCLASS()
class HYTABLE_API UHyDataTable : public UObject
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HyDataTable")
	UDataTable* DataTable;
};
