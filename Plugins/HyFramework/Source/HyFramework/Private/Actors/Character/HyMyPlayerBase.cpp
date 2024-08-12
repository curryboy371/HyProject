// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyMyPlayerBase.h"

//Input
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//Camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"

#include "HyCoreLogging.h"

AHyMyPlayerBase::AHyMyPlayerBase()
{

	CharacterDefaultSetup();
	ComponenetSetup();
}

void AHyMyPlayerBase::CharacterDefaultSetup()
{

	CameraBoomComp = nullptr;
	FollowCameraComp = nullptr;
}

void AHyMyPlayerBase::ComponenetSetup()
{
	CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomCom"));
	if (CameraBoomComp)
	{
		CameraBoomComp->SetupAttachment(RootComponent);
		CameraBoomComp->TargetArmLength = 800.0f;
		CameraBoomComp->bUsePawnControlRotation = true;
	}

	FollowCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraCom"));
	if (FollowCameraComp)
	{
		FollowCameraComp->SetupAttachment(CameraBoomComp, USpringArmComponent::SocketName);
		FollowCameraComp->bUsePawnControlRotation = false;
	}

}

void AHyMyPlayerBase::BeginPlay()
{
	Super::BeginPlay();


}

void AHyMyPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
