// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyCharacterBase.h"

#include "Math/UnrealMathUtility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"


#include "Components/ActionsSystemComponent.h"

#include "Animation/HyAnimInstance.h"

#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"

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

	if (ActionsSystemCom)
	{
		ActionsSystemCom->SetEquipActions(CharacterInitTagSet.EquipTag);

		FActionExcuteData InitActionData(CharacterInitTagSet.ActionTag);
		TriggerAction(InitActionData);
	}
	else
	{
		ERR_V("ActionsSystemCom is not set.");
	}
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

void AHyCharacterBase::InputAttack(const FInputActionValue& Value)
{
	if (UHyInst* HyInst = UHyInst::Get())
	{
		if (UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>())
		{
			TriggerAction(FActionExcuteData(TagManager->AttActionTagSet.ActionAttack, EActionPriority::EMedium), true);
		}
		else
		{
			ERR_V("TagManager is not set.");
		}
	}
}

void AHyCharacterBase::InputMove(const FInputActionValue& Value)
{
	if (!Controller)
	{
		ERR_V("No Controller");
		return;
	}

	CharacterInputData.bIsMoveInputing = true;
	bool bIsRotating = true; // 회전중인지 체크

	FVector2D MovementVector = Value.Get<FVector2D>();

	CharacterInputData.InputScale = MovementVector.Length();

	FRotator CurrentRotation = GetActorRotation();
	FRotator CameraRotation = Controller->GetControlRotation();

	// cam forward, right vector 
	FVector CameraForwardVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);
	FVector CameraRightVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

	// cam vector 기준으로 방향 설정
	FVector InputDirection = (CameraForwardVector * MovementVector.Y) + (CameraRightVector * MovementVector.X);

	CharacterInputData.SetInputDirection2D(InputDirection);
	CharacterInputData.SetInputRotator2D(CharacterInputData.InputDirection.Rotation());

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float AdjustedRotationSpeed = CharacterInputData.RotationSpeed * CharacterInputData.InputScale;

	// Rot to Quat
	FQuat CurrentQuat = FQuat(CurrentRotation);
	FQuat TargetQuat = FQuat(CharacterInputData.InputRotator);

	FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, DeltaTime, AdjustedRotationSpeed);
	FRotator NewRotation = NewQuat.Rotator();

	if (FMath::Abs(FMath::FindDeltaAngleDegrees(NewRotation.Yaw, CharacterInputData.InputRotator.Yaw)) < CharacterInputData.RotationToleranceAngle)
	{
		bIsRotating = false; // 회전 완료
	}

	// 항상 회전시킴
	// 회전이 완료되었더라도 오차 범위가 있는 회전값 계산이므로 (RotationToleranceAngle)
	SetActorRotation(NewRotation);

	// 회전이 완료되었으면 이동 처리 || 이미 이동중이면 그대로 이동
	FVector CharacterVelocity2D = FVector(1.f, 1.f, 0.f) * GetCharacterMovement()->Velocity;
	bool bCanMove = (CharacterVelocity2D.Length() > 0.0f);
	if (!bIsRotating || bCanMove)
	{
		AddMovementInput(CharacterInputData.InputDirection, CharacterInputData.InputScale); // 이동
		CharacterInputData.SetLastInputDirection();
	}
}

void AHyCharacterBase::InputJump(const FInputActionValue& Value)
{
	if (UHyInst* HyInst = UHyInst::Get())
	{
		if (UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>())
		{
			TriggerAction(FActionExcuteData(TagManager->NorActionTagSet.ActionJump, EActionPriority::EHigh));
		}
		else
		{
			ERR_V("TagManager is not set.");
		}
	}
}

void AHyCharacterBase::InputLook(const FInputActionValue& Value)
{

}

void AHyCharacterBase::InputEquip(const FInputActionValue& Value)
{
	if (UHyInst* HyInst = UHyInst::Get())
	{
		if (UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>())
		{
			TriggerAction(FActionExcuteData(TagManager->NorActionTagSet.ActionEquip, EActionPriority::EMedium));
		}
		else
		{
			ERR_V("TagManager is not set.");
		}
	}
}

