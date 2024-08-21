// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "GameplayTagContainer.h"


#include "HyTypes.generated.h"

#pragma region HyFrameworkEnum


UENUM(BlueprintType)
enum class EPPMType : uint8
{
	EPPM_None            UMETA(DisplayName = "EPPM_None"),
	EPPM_Stencil         UMETA(DisplayName = "EPPM_Stencil"),
	EPPM_Blur            UMETA(DisplayName = "EPPM_Blur"),
	EPPM_SprintBlur      UMETA(DisplayName = "EPPM_SprintBlur"),
	EPPM_MAX             UMETA(DisplayName = "EPPM_MAX"),
};

UENUM(BlueprintType)
enum class EStencilOutLine : uint8
{
	EStencil_MyPlayer UMETA(DisplayName = "EStencil_MyPlayer"),
	EStencil_2 UMETA(DisplayName = "EStencil_2"),
	EStencil_3 UMETA(DisplayName = "EStencil_3"),
	EStencil_4 UMETA(DisplayName = "EStencil_4"),
	EStencil_5 UMETA(DisplayName = "EStencil_5"),
	EStencil_6 UMETA(DisplayName = "EStencil_6"),
	EStencil_7 UMETA(DisplayName = "EStencil_7"),
	EStencil_8 UMETA(DisplayName = "EStencil_8"),
	EStencil_9 UMETA(DisplayName = "EStencil_9"),
	EStencil_10 UMETA(DisplayName = "EStencil_10"),
	EStencil_11 UMETA(DisplayName = "EStencil_11"),
	EStencil_12 UMETA(DisplayName = "EStencil_12"),
	EStencil_13 UMETA(DisplayName = "EStencil_13"),
	EStencil_14 UMETA(DisplayName = "EStencil_14"),
	EStencil_15 UMETA(DisplayName = "EStencil_15"),
};



enum class EDebugWidgetTextType : uint8
{
	EDebugText_EquipTag = 0,
	EDebugText_CurActionTag,
	EDebugText_StoredActionTag,
	EDebugText_CombatMode,
	EDebugText_Direction,

	EDebugText_CurLocomotion,
	EDebugText_TargetLocomotion,

	EDebugText_VelocityLength,

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
