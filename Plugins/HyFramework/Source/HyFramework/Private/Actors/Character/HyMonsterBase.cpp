// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyMonsterBase.h"
#include "Components/HyCharacterMovementComponent.h"

AHyMonsterBase::AHyMonsterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CharacterAIDefaultSetup();
}

void AHyMonsterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHyMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
