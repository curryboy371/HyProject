// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TableCreater.generated.h"

/**
 * 
 */
UCLASS()
class NPTABLE_API UTableCreater : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void CreateTable(bool forceupdate);
	static void CreateTableUasset(UScriptStruct* srtucttarget, bool forceupdate);

	static FName GetMetaKey() {return "CustomMeta";}
	static FName GetMetaValue() {return "TableEntity";}
};
