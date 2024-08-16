// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyCharacterBase.h"

#include "Math/UnrealMathUtility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/WidgetComponent.h"



#include "Components/ActionsSystemComponent.h"

#include "Animation/HyAnimInstance.h"

#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"

// Widget
#include "UI/Widget/HyDebugCharacterHudWidget.h"


#include "HyCoreDeveloperSettings.h"
#include "HyCoreMacro.h"


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
	if (!GetCapsuleComponent())
	{
		ERR_V("GetCapsuleComponent is not set.");
		return;
	}

	// Actions System Com
	ActionsSystemComp = CreateDefaultSubobject<UActionsSystemComponent>(TEXT("ActionsSystemComp"));
	if(!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
	}

	HUDLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("HUDLocationComp"));
	if (HUDLocationComp)
	{
		HUDLocationComp->SetupAttachment(GetCapsuleComponent());
		HUDLocationComp->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleRadius()));
	}

	DebugWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("DebugWidgetComp"));
	if (DebugWidgetComp)
	{
		DebugWidgetComp->SetupAttachment(HUDLocationComp);

		//FString DebugWidgetPath = TEXT("/Game/UI/Widget/Debug/HUD/HudDebugWidget.HudDebugWidget_C");
		//
		//UClass* DebugWidgetBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, *DebugWidgetPath);
		//if (DebugWidgetBPClass == nullptr)
		//{
		//	ERR_V("DebugWidgetBPClass is invalid %s", *DebugWidgetPath);
		//}
		//else
		//{
		//	if (DebugWidgetComp)
		//	{
		//		DebugWidgetComp->SetWidgetClass(DebugWidgetBPClass);
		//		DebugWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
		//	}
		//}
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

	DebugUpdate();
}

// Called to bind functionality to input
void AHyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

const bool AHyCharacterBase::IsDead()
{
	return CharacterStateData.bIsDead;
}

const bool AHyCharacterBase::IsCombatMode()
{
	return CharacterStateData.CombatMode == ECombatMode::ECombat;
}

FGameplayTag AHyCharacterBase::GetEquipTag()
{
	return CharacterStateData.TagName;
}

void AHyCharacterBase::SetCombatMode(const bool bCombatMode)
{
	if (!HyAnimInstance)
	{
		ERR_V("HyAnimInstance is not set.");
		return;
	}

	if (bCombatMode)
	{
		CharacterStateData.CombatMode = ECombatMode::ECombat;
	}
	else
	{
		CharacterStateData.CombatMode = ECombatMode::EPeace;
	}

	HyAnimInstance->SetCharacterStateData(CharacterStateData);
}

void AHyCharacterBase::CharacterSetup()
{
	// BeginPlay에서 Character를 Setup하는 함수
	SetHyAnimInstance();

	SwitchEquipLayer(CharacterInitTagSet.EquipTag);

	if (ActionsSystemComp)
	{
		ActionsSystemComp->SetEquipActions(CharacterInitTagSet.EquipTag);

		FActionExcuteData InitActionData(CharacterInitTagSet.ActionTag);
		ActionsSystemComp->SetDefaultActinoTag(InitActionData);
		TriggerAction(InitActionData);
	}
	else
	{
		ERR_V("ActionsSystemComp is not set.");
	}
}

void AHyCharacterBase::SwitchEquipLayer(const FGameplayTag& InEquipTag)
{
	if(!HyAnimInstance)
	{
		ERR_V("HyAnimInstance is not set.");
		return;
	}

	CharacterStateData.TagName = InEquipTag;

	HyAnimInstance->SetEquipLayer(InEquipTag);
	HyAnimInstance->SetCharacterStateData(CharacterStateData);
	
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

bool AHyCharacterBase::TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext, bool bCanBeStored)
{
	bool bSuccessAction = false;
	if (ActionsSystemComp)
	{
		InActionExcuteData.ActionContext = InContext;
		bSuccessAction = ActionsSystemComp->TriggerAction(InActionExcuteData, bCanBeStored);

		if (bSuccessAction)
		{

		}
	}

	return bSuccessAction;
	return false;
}

void AHyCharacterBase::InputAttack(const FInputActionValue& Value)
{
	if (UHyInst* HyInst = UHyInst::Get())
	{
		if (UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>())
		{
			TriggerAction(TagManager->ActionExcuteSet.ActionAttack, FString(), true);
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
			TriggerAction(TagManager->ActionExcuteSet.ActionJump);
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
			FString Context = TEXT("Auto");
			if(IsCombatMode())
			{
				TriggerAction(TagManager->ActionExcuteSet.ActionUnEquip, Context);
			}
			else
			{
				TriggerAction(TagManager->ActionExcuteSet.ActionEquip, Context);
			}
		}
		else
		{
			ERR_V("TagManager is not set.");
		}
	}
}

void AHyCharacterBase::DebugUpdate()
{
	if (const UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSetting())
	{
		bool bIsDebugDraw = DevSetting->IsDebugDraw();

		if (bIsDebugDraw)
		{
			DebugRenderWidget();
		}
	}
}

void AHyCharacterBase::DebugRenderWidget()
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is invalid");
		return;
	}

	if (!DebugWidgetComp)
	{
		ERR_V("DebugWidgetComp is invalid");
		return;
	}


	if (HyAnimInstance == nullptr)
	{
		ERR_V("HyAnimInstance is null");
		return;
	}

	if (DebugWidgetComp->GetWidget())
	{
		if (UHyDebugCharacterHudWidget* HyDebugCharacterHudWidget = Cast<UHyDebugCharacterHudWidget>(DebugWidgetComp->GetWidget()))
		{
			//bool bIsPlayer = false;
			//if (FNPTags::Get().PlayerTag == CharacterTag)
			//{
			//	bIsPlayer = true;
			//}
			//HudDebugWidget->SetIsPlayerInfo(bIsPlayer);

			int32 MontageIndex = -1;

			UAnimMontage* CurrentAnimMontage = GetCurrentMontage();

			if (CurrentAnimMontage && HyAnimInstance)
			{
				float MontagePosition = HyAnimInstance->Montage_GetPosition(CurrentAnimMontage);
				MontageIndex = CurrentAnimMontage->GetSectionIndexFromPosition(MontagePosition);
			}

			ActionsSystemComp->GetCurActionData();
			ActionsSystemComp->GetStoredActionData();

			HyDebugCharacterHudWidget->SetActionInfo(CharacterStateData.TagName, ActionsSystemComp->GetCurActionData(), ActionsSystemComp->GetStoredActionData(), MontageIndex);
			//HyDebugCharacterHudWidget->SetActionState(GetPerformingActionTag());
			//HyDebugCharacterHudWidget->SetTargetInfo(MyGuid, TargetGuid);

			//FString CharacterVelocityStr = FString::Printf(TEXT("%d %d %d"), (int32)AnimInst->GetCharacterVelocity2D().X, (int32)AnimInst->GetCharacterVelocity2D().Y, (int32)AnimInst->GetCharacterVelocity2D().Z);
			//FString CharacterAccelerStr = FString::Printf(TEXT("%d %d %d"), (int32)AnimInst->GetAcceleration2D().X, (int32)AnimInst->GetAcceleration2D().Y, (int32)AnimInst->GetAcceleration2D().Z);
			//
			//FString InputScaleStr = FString::Printf(TEXT("%.1f"), InputScale);
			//
			//FString VelocityToAccRatioStr = FString::Printf(TEXT("%.1f"), AnimInst->GetVelocityToAccelerationRatio());
			//
			//
			//HudDebugWidget->SetMoveInto(CharacterAccelerStr, CharacterVelocityStr, InputScaleStr, VelocityToAccRatioStr);

			//HudDebugWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			ERR_V("Casting HudDebugWidget is invalid");
		}
	}
	else
	{
		ERR_V("DebugWidgetCom Widget is null");
	}


}

