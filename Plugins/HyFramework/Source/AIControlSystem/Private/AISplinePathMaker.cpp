// Fill out your copyright notice in the Description page of Project Settings.


#include "AISplinePathMaker.h"
#include "Components/SplineComponent.h"

// Sets default values
AAISplinePathMaker::AAISplinePathMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
}

// Called when the game starts or when spawned
void AAISplinePathMaker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISplinePathMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAISplinePathMaker::AddSplinePoint(const FVector& InWorldPos)
{
	if (SplineComp)
	{
		SplineComp->AddSplinePoint(InWorldPos, ESplineCoordinateSpace::World);
	}
}

void AAISplinePathMaker::SetSplinePoints(const TArray<FVector>& InWorldPos)
{
	if (SplineComp)
	{
		SplineComp->SetSplinePoints(InWorldPos, ESplineCoordinateSpace::World);
	}
}

