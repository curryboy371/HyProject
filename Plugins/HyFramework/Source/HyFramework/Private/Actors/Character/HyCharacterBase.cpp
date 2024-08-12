// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"


#include "Components/ActionsSystemComponent.h"

#include "Animation/HyAnimInstance.h"

#include "HyCoreLogging.h"


// Sets default values
AHyCharacterBase::AHyCharacterBase()
{


	CharacterDefaultSetup();

	ComponenetSetup();
}

void AHyCharacterBase::CharacterDefaultSetup()
{
	HyAnimInstance = nullptr;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 500.0f); // ...at this rotation rate
}

void AHyCharacterBase::ComponenetSetup()
{
	// Actions System Com
	ActionsSystemCom = CreateDefaultSubobject<UActionsSystemComponent>(TEXT("ActionsSystemCom"));
	if(!ActionsSystemCom)
	{
		ERR_V("ActionsSystemCom is not set.");
	}




}

// Called when the game starts or when spawned
void AHyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterSetup();
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

void AHyCharacterBase::CharacterSetup()
{
	// BeginPlay에서 Character를 Setup하는 함수
	SetHyAnimInstance();

	SwitchEquipLayer(CharacterInitTagSet.EquipTag);

	FActionExcuteData InitActionData(CharacterInitTagSet.ActionTag);
	TriggerAction(InitActionData);
}

void AHyCharacterBase::SwitchEquipLayer(const FGameplayTag& InEquipTag)
{
	if(!HyAnimInstance)
	{
		ERR_V("HyAnimInstance is not set.");
		return;
	}

	HyAnimInstance->SetEquipLayer(InEquipTag);

	OnEquipLayerChanged.Broadcast(InEquipTag);
}

void AHyCharacterBase::SetHyAnimInstance()
{
	if (GetMesh())
	{
		HyAnimInstance = Cast<UHyAnimInstance>(GetMesh()->GetAnimInstance());
	}
	else
	{
		ERR_V("HyAnimInstance is not set.");
	}
}

bool AHyCharacterBase::TriggerAction(const FActionExcuteData& InActionExcuteData, bool bCanBeStored)
{
	bool bSuccessAction = false;
	if (ActionsSystemCom)
	{
		bSuccessAction = ActionsSystemCom->TriggerAction(InActionExcuteData, bCanBeStored);

		if (bSuccessAction)
		{

		}
	}

	return bSuccessAction;
}

