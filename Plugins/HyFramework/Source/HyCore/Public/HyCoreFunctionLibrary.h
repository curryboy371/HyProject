// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HyCoreTypes.h"

#include "HyCoreFunctionLibrary.generated.h"



/**
 * 
 */
UCLASS()
class HYCORE_API UHyCoreFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static float CalcDistanceBetweenCharacter(const ACharacter* characterA, const ACharacter* characterB);
		
	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawArrow(UObject* World, const FVector& LineStart, const FVector& LineEnd, float ArrowSize = 30.f, FLinearColor Color = FLinearColor::Green, float Duration = 0.f, float Tickness = 3.f);

	
	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawSphere(UWorld* World, const FVector Center, float Radius, int32 Segments = 12, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f);

	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawPointer(UWorld* World, const FVector Position, float Size, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f);
	
	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawBox(UWorld* World, const FVector BoxLocation, const FVector BoxExtent, const FRotator Rotation = FRotator::ZeroRotator, const FColor Color = FColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f);
	
	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawCapsule(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FRotator Rotation, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f);
	
	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawCapsuleQuat(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FQuat Rotation, const FColor Color = FColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f);

	UFUNCTION(BlueprintCallable, Category = "HyCore | Debug")
	static void DrawDebugCircle(UWorld* World, FVector Center, float Radius, int32 Segments, FColor Color, float Duration = 0.0f);

	static FString HyDirectionToString(EHyDirection InDirection)
	{
		switch (InDirection)
		{
		case EHyDirection::Front:
			return TEXT("Front");
		case EHyDirection::Back:
			return TEXT("Back");
		case EHyDirection::Left:
			return TEXT("Left");
		case EHyDirection::Right:
			return TEXT("Right");
		default:
			return TEXT("Unknown");
		}
	}
};
