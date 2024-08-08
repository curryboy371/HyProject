// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "LoggingDeveloperSettings.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


#include "LoggingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOGGINGSYSTEM_API ULoggingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

		
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawArrow(UObject* World, const FVector& LineStart, const FVector& LineEnd, float ArrowSize = 30.f, FLinearColor Color = FLinearColor::Green, float Duration = 0.f, float Tickness = 3.f)
	{
		if (World)
		{
			if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
			{
				if (DevSetting->IsDebugDraw())
				{
					UKismetSystemLibrary::DrawDebugArrow(World, LineStart, LineEnd, ArrowSize, Color, Duration, Tickness);
				}
			}
	
		}
	}
	
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawSphere(UWorld* World, const FVector Center, float Radius, int32 Segments = 12, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f)
	{
		if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				UKismetSystemLibrary::DrawDebugSphere(World, Center, Radius, Segments, Color, LifeTime, Thickness);
			}
		}
	}
	
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawPointer(UWorld* World, const FVector Position, float Size, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f)
	{
		if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				UKismetSystemLibrary::DrawDebugPoint(World, Position, Size, Color, LifeTime);
			}
		}
	}
	
	
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawBox(UWorld* World, const FVector BoxLocation, const FVector BoxExtent, const FRotator Rotation = FRotator::ZeroRotator, const FColor Color = FColor::Green,  float LifeTime = 0.0f, float Thickness = 3.0f)
	{
		if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				UKismetSystemLibrary::DrawDebugBox(World, BoxLocation, BoxExtent, Color, Rotation, LifeTime, Thickness);
			}
		}
	}
	
	
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawCapsule(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FRotator Rotation, const FLinearColor Color = FLinearColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f)
	{
		if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				UKismetSystemLibrary::DrawDebugCapsule(World, Center, HalfHeight, Radius, Rotation, Color, LifeTime, Thickness);
			}
		}
	}
	
	UFUNCTION(BlueprintCallable, Category = "Logging | Debug")
	static void DrawCapsuleQuat(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FQuat Rotation, const FColor Color = FColor::Green, float LifeTime = 0.0f, float Thickness = 3.0f)
	{
		if (const ULoggingDeveloperSettings* DevSetting = ULoggingDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDebugDraw())
			{
				DrawDebugCapsule(World, Center, HalfHeight, Radius, Rotation, Color, false, LifeTime,  0, Thickness);
			}
		}
	}
	
	
	
};
