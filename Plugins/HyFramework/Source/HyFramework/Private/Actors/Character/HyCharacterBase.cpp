// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/HyCharacterBase.h"

#include "Math/UnrealMathUtility.h"

//#include "GameFramework/CharacterMovementComponent.h"
#include "Components/HyCharacterMovementComponent.h"


#include "Components/SkeletalMeshComponent.h"

#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"


// Components
#include "Components/ActionsSystemComponent.h"
#include "Components/HyInventorySystemComponent.h"
#include "Components/HyCollisionSystemComponent.h"

#include "Animation/HyAnimInstance.h"

#include "Game/HyGameInstance.h"
#include "Manager/HyTagManager.h"
#include "Manager/HySpawnManager.h"


// Widget
#include "UI/Debug/SHyCharacterHudDebugWidget.h"
#include "Widgets/SWeakWidget.h" 

#include "HyCoreDeveloperSettings.h"
#include "HyCoreMacro.h"

#include "HyCoreFunctionLibrary.h"
#include "CControlFunctionLibrary.h"

#include "HyTypes.h"
#include "InvenTypes.h"
#include "CollisionTypes.h"


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
	SetActorHiddenInGame(true);

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

	// Mesh
	FRotator MeshRotator = FRotator(0.0f, -90.0f, 0.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), MeshRotator);


	// Character Guid
	MyGuid.Invalidate();
	TargetGuid.Invalidate();
}

void AHyCharacterBase::ComponenetSetup()
{
	// Actions System Com
	ActionsSystemComp = CreateDefaultSubobject<UActionsSystemComponent>(TEXT("ActionsSystemComp"));
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
	}


	CollisionSystemComp = CreateDefaultSubobject<UHyCollisionSystemComponent>(TEXT("CollisionSystemComp"));
	if (!CollisionSystemComp)
	{
		ERR_V("CollisionSystemComp is not set.");
	}

	InventorySystemComp = CreateDefaultSubobject<UHyInventorySystemComponent>(TEXT("InventorySystemComp"));
	if (!InventorySystemComp)
	{
		ERR_V("InventorySystemComp is not set.");
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
	else
	{
		ERR_V("HUDLocationComp is not set.");
	}

	CombatArrowParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CombatArrowParentComp"));
	if (CombatArrowParentComp)
	{
		CombatArrowParentComp->SetupAttachment(GetMesh());
		CharacterCombatArrowSetup();
	}


	// TODO 이 위치에 Add하면 beginplay시점에 CollisionSystemComp가 사라짐. 이유를 모르겠음.
	//HyActorComponents.Add(ActionsSystemComp);
	//HyActorComponents.Add(CollisionSystemComp);
	//HyActorComponents.Add(InventorySystemComp);
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


	SetActorHiddenInGame(false);
}

// Called every frame
void AHyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// CollisionINfo Update
	// tag


	DebugUpdate();


}

// Called to bind functionality to input
void AHyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

const bool AHyCharacterBase::IsTargetAvailable()
{

	return false;
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

const bool AHyCharacterBase::IsCrouching() const
{
	if (bIsCrouched == 1)
	{
		return true;
	}

	return false;
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
	MyGuid = FGuid::NewGuid();

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
	HyActorComponents.Reset();
	
	HyActorComponents.Add(ActionsSystemComp);
	HyActorComponents.Add(CollisionSystemComp);
	HyActorComponents.Add(InventorySystemComp);

	for(auto & ActorComp : HyActorComponents)
	{
		if (ActorComp)
		{
			ActorComp->InitializeHyActorComponent();
		}
	}



}

void AHyCharacterBase::CharacterCombatArrowSetup()
{
	if (!CombatArrowParentComp)
	{
		ERR_V("CombatArrowParentComp is not set.");
		return;
	}

	if (!GetMesh())
	{
		ERR_V("Mesh is not set.");
		return;
	}

	if (CombatArrowParentComp)
	{
		FRotator MeshRotation = GetMesh()->GetRelativeRotation();
		FVector ForwardVector = FRotationMatrix(MeshRotation).GetUnitAxis(EAxis::X);
		FVector RightVector = FRotationMatrix(MeshRotation).GetUnitAxis(EAxis::Y);

		for (int32 i = static_cast<int32>(ECombatDirection::EForward); i < static_cast<int32>(ECombatDirection::EDirectionMax); ++i)
		{
			ECombatDirection Direction = static_cast<ECombatDirection>(i);

			TObjectPtr<UArrowComponent> ArrowCom = nullptr;
			FName ArrowName;
			FVector ArrowLocation;

			switch (Direction)
			{
			case ECombatDirection::EForward:
				ArrowName = TEXT("FCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = ForwardVector;
				break;
			case ECombatDirection::ERight:
				ArrowName = TEXT("RCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = RightVector;
				break;
			case ECombatDirection::ELeft:
				ArrowName = TEXT("LCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = RightVector * -1;
				break;
			case ECombatDirection::EBack:
				ArrowName = TEXT("BCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = ForwardVector * -1;
				break;
			case ECombatDirection::EForwardRight:
				ArrowName = TEXT("FRCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = (ForwardVector + RightVector).GetSafeNormal();
				break;
			case ECombatDirection::EForwardLeft:
				ArrowName = TEXT("FLCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = (ForwardVector + (RightVector * -1)).GetSafeNormal();
				break;
			case ECombatDirection::EBackRight:
				ArrowName = TEXT("BRCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = ((ForwardVector * -1) + RightVector).GetSafeNormal();
				break;
			case ECombatDirection::EBackLeft:
				ArrowName = TEXT("BLCombatArrowCom");
				ArrowCom = CreateDefaultSubobject<UArrowComponent>(ArrowName);
				ArrowLocation = ((ForwardVector * -1) + (RightVector * -1)).GetSafeNormal();
				break;
			default:
				break;
			}

			if (ArrowCom)
			{
				FRotator ArrowRot = FRotator::ZeroRotator;
				ArrowRot.Pitch = 90;

				ArrowCom->SetupAttachment(CombatArrowParentComp);
				ArrowCom->SetRelativeLocation(ArrowLocation);
				ArrowCom->SetRelativeRotation(ArrowRot);
				CombatArrowComponentMap.Add(Direction, ArrowCom);
			}
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

void AHyCharacterBase::MatchArrowComponenLocation()
{
	for (auto& CombatArrowPair : CombatArrowComponentMap)
	{
		if (CombatArrowPair.Value)
		{
			FVector RelativeLoc = CombatArrowPair.Value->GetRelativeLocation() * GetCapsuleComponent()->GetScaledCapsuleRadius() * 2;
			CombatArrowPair.Value->SetRelativeLocation(RelativeLoc);
		}
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

void AHyCharacterBase::SetStencilOutline(bool IsShow, EStencilOutLine StencilType)
{
	if (TObjectPtr<USkeletalMeshComponent> SkeletalMesh = GetMesh())
	{
		SkeletalMesh->SetRenderCustomDepth(IsShow);
		SkeletalMesh->CustomDepthStencilValue = (int32)StencilType;
		SkeletalMesh->SetVisibility(false);
		SkeletalMesh->SetVisibility(true);
	}

}

bool AHyCharacterBase::GetClosestCombatArrow(const FVector& InAttackerLocation, const float InOwnerAttackRange, FVector& OutCombatArrowLocation)
{
	bool bRes = false;
	OutCombatArrowLocation = InAttackerLocation;

	float ClosetDistance = InOwnerAttackRange;

	for (auto& CombatArrowPair : CombatArrowComponentMap)
	{
		if (CombatArrowPair.Value)
		{
			FVector Distance = CombatArrowPair.Value->GetComponentLocation() - InAttackerLocation;
			float DistanceLength = Distance.Length();

			if (DistanceLength < ClosetDistance)
			{
				ClosetDistance = DistanceLength;
				OutCombatArrowLocation = CombatArrowPair.Value->GetComponentLocation();
				bRes = true;
			}
		}
	}

	return bRes;
}

void AHyCharacterBase::SetDashWarpingTarget(const FVector& InTargetLocation)
{
	if (!MotionWarpingComp)
	{
		ERR_V("MotionWarpingComp is not set.");
		return;
	}

	FTransform TargetTransform = GetTransform();
	TargetTransform.SetLocation(InTargetLocation);

	FVector LookVec = InTargetLocation - GetActorLocation();
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVec).Rotator();
	TargetRot.Pitch = 0;
	FQuat QuatRot = TargetRot.Quaternion();
	TargetTransform.SetRotation(QuatRot);

	MotionWarpingComp->AddOrUpdateWarpTargetFromTransform(FName("Dash"), TargetTransform);
}

void AHyCharacterBase::ReleaseWarpingTarget()
{
	if (!MotionWarpingComp)
	{
		ERR_V("MotionWarpingComp is not set.");
		return;
	}

	MotionWarpingComp->RemoveWarpTarget(FName("Dash"));
}

bool AHyCharacterBase::TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext, bool bCanBeStored)
{
	bool bSuccessAction = false;

	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return bSuccessAction;
	}


	InActionExcuteData.ActionContext = InContext;
	bSuccessAction = ActionsSystemComp->TriggerAction(InActionExcuteData, bCanBeStored);

	if (bSuccessAction)
	{

	}

	return bSuccessAction;
}

void AHyCharacterBase::SetStoredAction(FActionExcuteData& InActionExcuteData, const FString InContext, bool bForce)
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return;
	}

	InActionExcuteData.ActionContext = InContext;
	ActionsSystemComp->SetStoredActionTag(InActionExcuteData, bForce);

}

void AHyCharacterBase::HandleAction(EActionHandleType InExitType, float BlendOut)
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return;
	}

	switch (InExitType)
	{
	case EActionHandleType::EActionHandle_Free:
		ActionsSystemComp->FreeAction();
		break;
	case EActionHandleType::EActionHandle_Stop:
		ActionsSystemComp->ActionStopImmeditaley(BlendOut);
		break;
	case EActionHandleType::EActionHandle_ConditionalStop:
		if (ActionsSystemComp->IsActionStopCondition()) // 조건이 일치하면 Stop
		{
			HandleAction(EActionHandleType::EActionHandle_Stop, BlendOut);
		}
		break;
	case EActionHandleType::EActionHandle_Noti:
		ActionsSystemComp->ActionNotify();
		break;
	default:
		break;
	}
}

void AHyCharacterBase::SetPerformingActionPriority(EActionPriority InPriority)
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return;
	}

	ActionsSystemComp->SetCurActionPriority(InPriority);
}

bool AHyCharacterBase::CompareCurrentPriority(EActionPriority InPriority) const
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return false;
	}

	return ActionsSystemComp->GetCurActionData().ActionPriority < InPriority;
}

const bool AHyCharacterBase::IsEmptyStoredAction() const
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return false;
	}

	return ActionsSystemComp->IsEmptyStoredAction();
}

const bool AHyCharacterBase::IsCanStoreAction(EActionPriority InPriority) const
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return false;
	}

	if (!ActionsSystemComp->IsEmptyStoredAction())
	{
		return ActionsSystemComp->GetStoredActionData().ActionPriority < InPriority;
	}

	return true;
}

const FGameplayTag AHyCharacterBase::GetCurAction() const
{
	if (ActionsSystemComp) 
	{
		return ActionsSystemComp->GetPerformingActionTag();
	}

	return FGameplayTag();
}

const FGameplayTag AHyCharacterBase::GetStoredAction() const
{
	if (ActionsSystemComp)
	{
		return ActionsSystemComp->GetStoredActionData().TagName;
	}

	return FGameplayTag();
}

void AHyCharacterBase::InputAttack(const FInputActionValue& Value)
{
	if (!InventorySystemComp)
	{
		ERR_V("InventorySystemComp is not set.");
		return;
	}

	if (InventorySystemComp->GetWeaponArmState() == EWeaponArmState::EWS_None)
	{
		// 장착한 무기가 없음
		return;
	}

	UHyInst* HyInst = UHyInst::Get();
	if(!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if(!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}


	if (!IsCanAction(EKeyInput::IA_Attack))
	{
		return;
	}

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

void AHyCharacterBase::InputMove(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

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

	if (!IsCanAction(EKeyInput::IA_Move))
	{
		return;
	}

	TriggerAction(TagManager->ActionExcuteSet.ActionMove);

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

void AHyCharacterBase::CompletedMove(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is invalid");
		return;
	}

	FGameplayTag CurActionTag = ActionsSystemComp->GetPerformingActionTag();
	if (TagManager->ActionExcuteSet.ActionMove.TagName == CurActionTag)
	{
		TriggerAction(TagManager->ActionExcuteSet.ActionIdle);
	}
}

void AHyCharacterBase::InputJump(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	if (!IsCanAction(EKeyInput::IA_Jump))
	{
		return;
	}

	TriggerAction(TagManager->ActionExcuteSet.ActionJump);

}

void AHyCharacterBase::InputLook(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHyCharacterBase::InputEquip(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	if (!InventorySystemComp)
	{
		ERR_V("InventorySystemComp is not set.");
		return;
	}

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

void AHyCharacterBase::InputSprint(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}


	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	if (!IsCanAction(EKeyInput::IA_Sprint))
	{
		return;
	}

	HyCharacterMovement->AccelerateToNextState();
}

void AHyCharacterBase::CompletedSprint(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	HyCharacterMovement->SetDefaultLocomotionState();
}

void AHyCharacterBase::InputCrouch(const FInputActionValue& Value)
{
	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return;
	}

	if (!IsCanAction(EKeyInput::IA_Crouch))
	{
		return;
	}

	TriggerAction(TagManager->ActionExcuteSet.ActionCrouching);
}

void AHyCharacterBase::EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet)
{
	if (!CollisionSystemComp)
	{
		ERR_V("CollisionSystemComp is invalid");
		return;
	}

	CollisionSystemComp->EnableAttackCollider(InAttackCollisionSet);


}

void AHyCharacterBase::DisableAttackCollider()
{
	if (!CollisionSystemComp)
	{
		ERR_V("CollisionSystemComp is invalid");
		return;
	}

	CollisionSystemComp->DisableAttackCollider();
}

float AHyCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead())
	{
		return 0.0f;
	}


	LOG_V("TakeDamage : %f", Damage);



	return 0.0f;
}

const bool AHyCharacterBase::IsDead() const
{
	if (IsPendingKillPending())
	{
		return true;
	}

	if (CharacterStateData.bIsDead)
	{
		return true;
	}

	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is invalid");
		return true;
	}

	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return true;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return true;
	}

	if(TagManager->IsDeadAction(ActionsSystemComp->GetPerformingActionTag()))
	{
		return true;
	}

	return false;
}

const bool AHyCharacterBase::IsCanAction(EKeyInput InKeyAction) const
{
	bool bRes = false;


	UHyInst* HyInst = UHyInst::Get();
	if (!HyInst)
	{
		ERR_V("HyInst is not set.");
		return bRes;
	}

	UHyTagManager* TagManager = HyInst->GetManager<UHyTagManager>();
	if (!TagManager)
	{
		ERR_V("TagManager is not set.");
		return bRes;
	}

	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is invalid");
		return bRes;
	}

	FGameplayTag CurActionTag= ActionsSystemComp->GetPerformingActionTag();

	switch (InKeyAction)
	{
	case EKeyInput::IA_None:
		break;
	case EKeyInput::IA_Attack:
		bRes = TagManager->IsNormalAction(CurActionTag);
		if (!bRes)
		{
			bRes = TagManager->IsAttackAction(CurActionTag);
		}
		break;
	case EKeyInput::IA_Equip:
		bRes = TagManager->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Skill1:
		bRes = TagManager->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Jump:
		bRes = TagManager->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Move:
	{
		bRes = TagManager->IsNormalAction(CurActionTag);
		if (!bRes)
		{
			if (TagManager->IsAttackAction(CurActionTag))
			{
				bRes = CompareCurrentPriority(TagManager->ActionExcuteSet.ActionMove.ActionPriority);
			}
		}
	}
		break;
	case EKeyInput::IA_Look:

		break;
	case EKeyInput::IA_Sprint:
		bRes = TagManager->IsNormalAction(CurActionTag);

		break;

	case EKeyInput::IA_Crouch:
		bRes = TagManager->IsNormalAction(CurActionTag);
		break;
	default:
		break;
	}

	return bRes;
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

			FString VelocitySpeed = FString::Printf(TEXT("%f"), GetVelocity().Length());
			SCharacterDebugWidget->UpdateDebugText(EDebugWidgetTextType::EDebugText_VelocityLength, VelocitySpeed);

			SCharacterDebugWidget->SetRenderTransform(FSlateRenderTransform(ScreenPosition));
		}
	}


}

