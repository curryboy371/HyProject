// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIControlFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AICONTROLSYSTEM_API UAIControlFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static float CalcDistanceBetweenCharacter(const ACharacter* characterA, const ACharacter* characterB);

};
