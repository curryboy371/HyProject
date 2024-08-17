// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "GameplayTagContainer.h"


#include "HyTypes.generated.h"

#pragma region HyFrameworkEnum

enum class EDebugWidgetTextType : uint8
{
	EDebugText_EquipTag = 0,
	EDebugText_CurActionTag,
	EDebugText_StoredActionTag,
	EDebugText_CombatMode,

	EDebugText_END,
};

#pragma endregion


#pragma region HyFrameworkStruct


#pragma endregion



/**
 * 
 */
UCLASS()
class HYFRAMEWORK_API UHyTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
