// Fill out your copyright notice in the Description page of Project Settings.


#include "HyCoreFunctionLibrary.h"
#include "HyCoreDeveloperSettings.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "GameFramework/Character.h"


float UHyCoreFunctionLibrary::CalcDistanceBetweenCharacter(const ACharacter* characterA, const ACharacter* characterB)
{
	// 바운드 볼륨 거리를 제외한 Character간 거리 계산
	if (characterA && characterB)
	{
		const FBox aBox = characterA->GetMesh()->Bounds.GetBox();
		const FBox bBox = characterB->GetMesh()->Bounds.GetBox();

		const float dist = characterA->GetDistanceTo(characterB);
		return dist - aBox.GetExtent().X - bBox.GetExtent().X;
	}
	return -1.0f;
}

void UHyCoreFunctionLibrary::DrawArrow(UObject* World, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, FLinearColor Color, float Duration, float Tickness)
{
	if (World)
	{
		if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
		{
			if (DevSetting->IsDrawEnable())
			{
				UKismetSystemLibrary::DrawDebugArrow(World, LineStart, LineEnd, ArrowSize, Color, Duration, Tickness);
			}
		}

	}
}

void UHyCoreFunctionLibrary::DrawSphere(UWorld* World, const FVector Center, float Radius, int32 Segments, const FLinearColor Color, float LifeTime, float Thickness)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{
			UKismetSystemLibrary::DrawDebugSphere(World, Center, Radius, Segments, Color, LifeTime, Thickness);
		}
	}
}

void UHyCoreFunctionLibrary::DrawPointer(UWorld* World, const FVector Position, float Size, const FLinearColor Color, float LifeTime)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{
			UKismetSystemLibrary::DrawDebugPoint(World, Position, Size, Color, LifeTime);
		}
	}
}

void UHyCoreFunctionLibrary::DrawBox(UWorld* World, const FVector BoxLocation, const FVector BoxExtent, const FRotator Rotation, const FColor Color, float LifeTime, float Thickness)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{
			UKismetSystemLibrary::DrawDebugBox(World, BoxLocation, BoxExtent, Color, Rotation, LifeTime, Thickness);
		}
	}
}

void UHyCoreFunctionLibrary::DrawCapsule(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FRotator Rotation, const FLinearColor Color, float LifeTime, float Thickness)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{
			UKismetSystemLibrary::DrawDebugCapsule(World, Center, HalfHeight, Radius, Rotation, Color, LifeTime, Thickness);
		}
	}
}

void UHyCoreFunctionLibrary::DrawCapsuleQuat(UWorld* World, const FVector Center, const float HalfHeight, const float Radius, const FQuat Rotation, const FColor Color, float LifeTime, float Thickness)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{
			DrawDebugCapsule(World, Center, HalfHeight, Radius, Rotation, Color, false, LifeTime, 0, Thickness);
		}
	}
}

void UHyCoreFunctionLibrary::DrawDebugCircle(UWorld* World, FVector Center, float Radius, int32 Segments, FColor Color, float Duration)
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		if (DevSetting->IsDrawEnable())
		{

			const float AngleStep = 2.0f * PI / Segments;
			FVector PreviousPoint = Center + FVector(Radius, 0, 0);

			for (int32 i = 1; i <= Segments; ++i)
			{
				const float Angle = i * AngleStep;
				FVector CurrentPoint = Center + FVector(Radius * FMath::Cos(Angle), Radius * FMath::Sin(Angle), 0);
				DrawDebugLine(World, PreviousPoint, CurrentPoint, Color, false, Duration);
				PreviousPoint = CurrentPoint;
			}
		}
	}
}
