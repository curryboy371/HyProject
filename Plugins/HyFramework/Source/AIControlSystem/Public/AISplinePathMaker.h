// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISplinePathMaker.generated.h"

UCLASS()
class AICONTROLSYSTEM_API AAISplinePathMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISplinePathMaker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintCallable, Category = AI)
	void AddSplinePoint(const FVector& InWorldPos);

	UFUNCTION(BlueprintCallable, Category = AI)
	void SetSplinePoints(const TArray<FVector>& InWorldPos);


protected:
	UPROPERTY(EditAnywhere, Category = AI)
	TObjectPtr<class USplineComponent> SplineComp;
};
