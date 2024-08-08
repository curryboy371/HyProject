// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HyCharacterBase.h"


// Sets default values
AHyCharacterBase::AHyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

