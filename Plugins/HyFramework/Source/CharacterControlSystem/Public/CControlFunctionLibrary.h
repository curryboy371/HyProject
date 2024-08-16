// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CControlFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERCONTROLSYSTEM_API UCControlFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CControl", meta = (BlueprintThreadSafe))
	static class UHyAnimInstance* GetOwningAnimInstance(UObject* Object);
	
};
