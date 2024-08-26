// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIControlTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAIState : uint8 
{
    EPatrol = 0 UMETA(DisplayName = "Patrol"),
    ECombat = 1 UMETA(DisplayName = "Combat"),
    EReturnHome = 3 UMETA(DisplayName = "Return Home"),
    EWait = 4 UMETA(DisplayName = "Wait"),
};

UENUM(BlueprintType)
enum class EPatrolType : uint8 
{
    EFollowSpline = 0 UMETA(DisplayName = "Follow Spline"),
    ERandomPoint = 1 UMETA(DisplayName = "Random Point In Range"),
};



USTRUCT(BlueprintType)
struct FBaseUnit 
{
    GENERATED_BODY()

public:
    FBaseUnit() {};

    FBaseUnit(const TSubclassOf<class AHyCharacterBase>& InClass)
    {
        AIClassBP = InClass;
    }
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    TSubclassOf<AHyCharacterBase> AIClassBP;
};

USTRUCT(BlueprintType)
struct FAISpawnInfo : public FBaseUnit 
{
    GENERATED_BODY()

    FAISpawnInfo()
    {
        AIClassBP = nullptr;
        SpawnTransform = FTransform();
    };

    FAISpawnInfo(const TSubclassOf<class AHyCharacterBase> InSpawnClass)
    {
        AIClassBP = InSpawnClass;
        SpawnTransform = FTransform();
    }

    FAISpawnInfo(const TSubclassOf<class AHyCharacterBase> InSpawnClass, const FTransform& InTransform)
    {
        AIClassBP = InSpawnClass;
        SpawnTransform = InTransform;
    }


    UPROPERTY(EditAnywhere, meta = (MakeEditWidget), BlueprintReadWrite, Category = Hy)
    FTransform SpawnTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Hy)
    TObjectPtr<class AAISplinePathMaker> PathMaker;
};

UCLASS()
class AICONTROLSYSTEM_API UAIControlTypes : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
