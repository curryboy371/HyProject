// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyCharacterBase.h"

#include "Math/UnrealMathUtility.h"

//#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HyCharacterMovementComponent.h"


#include "Components/SkeletalMeshComponent.h"

#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/WidgetComponent.h"



#include "Components/ActionsSystemComponent.h"
#include "Components/HyInventorySystemComponent.h"


#include "Animation/HyAnimInstance.h"

#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"


// Widget
#include "UI/Debug/SHyCharacterHudDebugWidget.h"
#include "Widgets/SWeakWidget.h" 

#include "HyCoreDeveloperSettings.h"
#include "HyCoreMacro.h"

#include "HyTypes.h"
#include "HyCoreFunctionLibrary.h"
#include "CControlFunctionLibrary.h"

#include "InvenTypes.h"


#include "Items/HyItem.h"
#include "Items/HyWeapon.h"

#include "HyTableSubsystem.h"
#include "Table/Item_TableEntity.h"


// MovementCom custom으로 변경
AHyCharacterBase::AHyCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	CharacterDefaultSetup();

	ComponenetSetup();
}

void AHyCharacterBase::CharacterDefaultSetup()
{
	HyAnimInstance = nullptr;
	HyCharacterMovement = nullptr;

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
	ActionsSystemComp = CreateDefaultSubobject<UActionsSystemComponent>(TEXT("ActionsSystemComp"));
	if (ActionsSystemComp)
	{
		HyActorComponents.Add(ActionsSystemComp);
	}

	InventorySystemComp = CreateDefaultSubobject<UHyInventorySystemComponent>(TEXT("InventorySystemComp"));
	if (InventorySystemComp)
	{
		HyActorComponents.Add(InventorySystemComp);
	}




	HyCharacterMovement = Cast<UHyCharacterMovementComponent>(GetCharacterMovement());
	if(!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
	}

	HUDLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("HUDLocationComp"));
	if (HUDLocationComp)
	{
		HUDLocationComp->SetupAttachment(GetCapsuleComponent());
		HUDLocationComp->SetRelativeLocation(FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleRadius()));
	}
}

// Called when the game starts or when spawned
void AHyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetHyAnimInstance();

	CharacterSetup();

	SwitchEquipLayer(CharacterDefaultTagSet.PeaceEquipTag);

	// DefaultAction Setting, Trigger Excute
	if (ActionsSystemComp)
	{
		FActionExcuteData InitActionData(CharacterDefaultTagSet.ActionTag);
		ActionsSystemComp->SetDefaultActinoTag(InitActionData);
		TriggerAction(InitActionData);
	}
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
	ECombatMode PreMode = CharacterStateData.CombatMode;
	CharacterStateData.SetCombatMode(bCombatMode);

	if (PreMode != CharacterStateData.CombatMode)
	{
		FGameplayTag NewEquipTag = CharacterStateData.CombatMode == ECombatMode::ECombat ? CharacterDefaultTagSet.CombatEquipTag : CharacterDefaultTagSet.PeaceEquipTag;

		SwitchEquipLayer(NewEquipTag);
	}



}

const bool AHyCharacterBase::IsWeaponOnHand()
{
	if (InventorySystemComp)
	{
		const EWeaponArmState ArmState = InventorySystemComp->GetWeaponArmState();

		switch (ArmState)
		{
		case EWeaponArmState::EWS_None:
			WAR_V("Equipped Weapon is None");
			break;
		case EWeaponArmState::EWS_Unarmed:
			return false;
		case EWeaponArmState::EWS_Armed:
			return true;
		default:
			break;
		}
	}
	else
	{
		ERR_V("InventorySystemComp is not set.");
	}

	return false;
}

void AHyCharacterBase::CharacterSetup()
{
	// BeginPlay에서 Character를 Setup하는 함수

	CharacterActorComponentSetup();

	CharacterWidgetSetup();

	SetDelegateFunctions();

	// Test Item Add
	if (UHyTableSubsystem* TableSubSystem = GetGameInstance()->GetSubsystem<UHyTableSubsystem>())
	{
		int32 TestItem = 1;
		if (FItem_TableEntity* ItemEntity = TableSubSystem->GetTableData<FItem_TableEntity>(TestItem))
		{
			InventorySystemComp->AddInventoryItem(*ItemEntity);
		}
		else
		{
			ERR_V("ItemEntity is not set. ID=%d", TestItem);
		}
	}

}

void AHyCharacterBase::CharacterActorComponentSetup()
{
	for(auto & ActorComp : HyActorComponents)
	{
		if (ActorComp)
		{
			ActorComp->InitializeHyActorComponent();
		}
	}


}

void AHyCharacterBase::SetDelegateFunctions()
{
	//  Bind Change Equip Action(Layer)
	if (HyAnimInstance)
	{
		OnEquipTagChanged.AddDynamic(HyAnimInstance, &UHyAnimInstance::SetEquipLayer);
	}
	if (ActionsSystemComp)
	{
		OnEquipTagChanged.AddDynamic(ActionsSystemComp, &UActionsSystemComponent::SetEquipActions);
	}
}

void AHyCharacterBase::CharacterWidgetSetup()
{
	CharacterDebugHudSetup();

}

void AHyCharacterBase::CharacterDebugHudSetup()
{
	// Create the HUD widget
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(SCharacterDebugWidget, SHyCharacterHudDebugWidget);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget).PossiblyNullContent(SCharacterDebugWidget.ToSharedRef())
		);
	}
}

void AHyCharacterBase::SwitchEquipLayer(const FGameplayTag& InEquipTag)
{
	CharacterStateData.TagName = InEquipTag;
	OnEquipTagChanged.Broadcast(CharacterStateData.TagName);
}

void AHyCharacterBase::SetHyAnimInstance()
{
	if (GetMesh())
	{
		HyAnimInstance = Cast<UHyAnimInstance>(GetMesh()->GetAnimInstance());
		if (HyAnimInstance)
		{
			HyAnimInstance->SetCharacterDefaultTagSet(CharacterDefaultTagSet);
		}
		else
		{
			ERR_V("HyAnimInstance is not set.");
		}

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
}

void AHyCharacterBase::InputAttack(const FInputActionValue& Value)
{
	if (UHyInst* HyInst = UHyInst::Get())
	{
		if (UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>())
		{
			if(IsCombatMode())
			{
				TriggerAction(TagManager->ActionExcuteSet.ActionAttack, FString(), true);
			}
			else
			{
				FString Context = TEXT("Auto");
				TriggerAction(TagManager->ActionExcuteSet.ActionEquip, Context);
			}
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
			if (InventorySystemComp)
			{
				FGameplayTag WeaponSlot = TagManager->ItemSlotTagSet.SlotWeapon;
				if (InventorySystemComp->IsEquippedSlot(WeaponSlot))
				{
					InventorySystemComp->UnEquipItemBySlot(WeaponSlot);
				}
				else
				{
					InventorySystemComp->EquipItemBySlot(WeaponSlot);
				}
			}
		}
	}

}

void AHyCharacterBase::InputSprint(const FInputActionValue& Value)
{
	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	HyCharacterMovement->AccelerateToNextState();
}

void AHyCharacterBase::CompletedSprint(const FInputActionValue& Value)
{
	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	HyCharacterMovement->SetDefaultLocomotionState();
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

	if (HyAnimInstance == nullptr)
	{
		ERR_V("HyAnimInstance is null");
		return;
	}

	if (SCharacterDebugWidget.IsValid() && GetWorld()->GetFirstPlayerController())
	{
		FVector2D ScreenPosition;
		if (GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(GetActorLocation() + CharacterDebugData.DebugWidgetLocation, ScreenPosition))
		{
			int32 MontageIndex = -1;
			UAnimMontage* CurrentAnimMontage = GetCurrentMontage();
			if (CurrentAnimMontage && HyAnimInstance)
			{
				float MontagePosition = HyAnimInstance->Montage_GetPosition(CurrentAnimMontage);
				MontageIndex = CurrentAnimMontage->GetSectionIndexFromPosition(MontagePosition);
			}

			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_EquipTag, CharacterStateData.TagName.ToString());

			FString CurAction = ActionsSystemComp->GetCurActionData().TagName.ToString() + FString::Printf(TEXT("(%d) Index(%d)"), ActionsSystemComp->GetCurActionData().ActionPriority, MontageIndex);
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_CurActionTag, CurAction);

			FString StoreAction = ActionsSystemComp->GetStoredActionData().TagName.ToString() + FString::Printf(TEXT("(%d)"), ActionsSystemComp->GetStoredActionData().ActionPriority);
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_StoredActionTag, StoreAction);

			FString CombatMode = (IsCombatMode()) ? TEXT("Combat") : TEXT("Peace");
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_CombatMode, CombatMode);

			FString Direction = FString::Printf(TEXT("%s(%f)"), *UHyCoreFunctionLibrary::HyDirectionToString(HyAnimInstance->GetVelocityData().SpeedDirection), HyAnimInstance->GetVelocityData().Direction);
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_Direction, Direction);

			FString CurLocomotion = FString::Printf(TEXT("%s"), *UCControlFunctionLibrary::LocomotionStateToString(HyAnimInstance->GetCurLocomotionState()));
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_CurLocomotion, CurLocomotion);

			FString TargetLocomotion = FString::Printf(TEXT("%s"), *UCControlFunctionLibrary::LocomotionStateToString(HyAnimInstance->GetTargetLocomotionState()));
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_TargetLocomotion, TargetLocomotion);

			SCharacterDebugWidget->SetRenderTransform(FSlateRenderTransform(ScreenPosition));
		}
	}


}

