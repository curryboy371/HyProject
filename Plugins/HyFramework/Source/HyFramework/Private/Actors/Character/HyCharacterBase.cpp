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
#include "Components/HyFXSystemComponent.h"


#include "Animation/HyAnimInstance.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"

#include "HyTagSubsystem.h"


// Widget
#include "UI/Debug/SHyCharacterHudDebugWidget.h"
#include "Widgets/SWeakWidget.h" 

#include "HyCoreDeveloperSettings.h"
#include "HyCoreMacro.h"

#include "HyCoreFunctionLibrary.h"
#include "CControlFunctionLibrary.h"

#include "InvenTypes.h"
#include "CollisionTypes.h"


#include "Items/HyItem.h"
#include "Items/HyWeapon.h"

#include "HyTableSubsystem.h"
#include "Table/Item_TableEntity.h"
#include "Table/SpawnInfo_TableEntity.h"


FQuickActionExcuteDataSet AHyCharacterBase::QuickActionExcute = FQuickActionExcuteDataSet();

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
	GetCharacterMovement()->RotationRate = FRotator(500.0f, 500.0f, 500.0f); // ...at this rotation rate

	// Mesh
	FRotator MeshRotator = FRotator(0.0f, -90.0f, 0.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), MeshRotator);


	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_HYCHARACTER);


	// Character Guid
	MyGuid.Invalidate();
	TargetGuid.Invalidate();

	AttackTrailType = EHyAttackTrailType::AttackHuman;
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

	FXSystemComponent = CreateDefaultSubobject<UHyFXSystemComponent>(TEXT("HyFXSystemComp"));
	if(!FXSystemComponent)
	{
		ERR_V("FXSystemComponent is not set.");
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

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp"));
	if(!MotionWarpingComp)
	{
		ERR_V("MotionWarpingComp is not set.");
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

	SpawnDefaultController();

	SetHyAnimInstance();

	CharacterSetup();

	SwitchEquipLayer(CharacterDefaultTagSet.PeaceEquipTag);

	// DefaultAction Setting, Trigger Excute
	if (ActionsSystemComp)
	{
		ActionsSystemComp->SetDefaultStandActinoTag(QuickActionExcute.Idle);
		ActionsSystemComp->SetDefaultAirActinoTag(QuickActionExcute.AirIdle);

		FActionExcuteData InitActionData(CharacterDefaultTagSet.ActionTag);
		TriggerAction(InitActionData);
	}


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
	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("Inst is not set.");
		return false;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if(!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return false;
	}

	if(TargetGuid.IsValid())
	{
		return SpawnManager->IsValidCharacter(TargetGuid);
	}

	return false;
}

const bool AHyCharacterBase::IsDead()
{
	return CharacterStateData.bIsDead;
}

const bool AHyCharacterBase::IsCombatMode() const
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

void AHyCharacterBase::SpawnCompleted(const int32 InSpawnID)
{
	// Spawn이 완료되었을때 호출되는 함수
	MyGuid = FGuid::NewGuid();

	SetGroundLocation();

	SetActorHiddenInGame(false);
	SpawnID = InSpawnID;
}

void AHyCharacterBase::SetGroundLocation()
{
	// 발 지면에 맞추기
	FVector SpawnLocation = GetActorLocation();
	FVector TraceStart = SpawnLocation;
	FVector TraceEnd = SpawnLocation - FVector(0, 0, 1000); // 발 아래 방향으로 트레이스

	FHitResult HitResult;
	// raycast
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility))
	{
		FVector HitLocation = HitResult.Location;
		SetActorLocation(FVector(SpawnLocation.X, SpawnLocation.Y, HitLocation.Z));
	}
}

void AHyCharacterBase::CharacterAIDefaultSetup()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->bRunPhysicsWithNoController = true;
}

void AHyCharacterBase::CharacterActionTagSetup()
{
	if (!QuickActionExcute.bIsInit)
	{
		if (UHyTagSubsystem* TagSubsystem = GET_TAG_SUBSYSTEM())
		{

			// TODO 확장성을 고려한다면 좋지 않은 방법
			// 이렇게 하면 액션 추가하거나 우선순위 변경되면 항상 수정해줘야함

			QuickActionExcute.Spawn = FActionExcuteData(TagSubsystem->ActionTagSet.ActionSpawn, EActionPriority::ENone);
			QuickActionExcute.Idle = FActionExcuteData(TagSubsystem->ActionTagSet.ActionIdle, EActionPriority::ENone);
			QuickActionExcute.Move = FActionExcuteData(TagSubsystem->ActionTagSet.ActionMove, EActionPriority::ELow);

			QuickActionExcute.AirIdle = FActionExcuteData(TagSubsystem->ActionTagSet.ActionAirIdle, EActionPriority::ENone);


			QuickActionExcute.Jump = FActionExcuteData(TagSubsystem->ActionTagSet.ActionJump, EActionPriority::EMedium);
			QuickActionExcute.Equip = FActionExcuteData(TagSubsystem->ActionTagSet.ActionEquip, EActionPriority::EMedium);
			QuickActionExcute.UnEquip = FActionExcuteData(TagSubsystem->ActionTagSet.ActionUnEquip, EActionPriority::EMedium);
			QuickActionExcute.Crouching = FActionExcuteData(TagSubsystem->ActionTagSet.ActionCrouching, EActionPriority::EMedium);

			QuickActionExcute.Attack = FActionExcuteData(TagSubsystem->ActionTagSet.ActionAttack, EActionPriority::EMedium);
			QuickActionExcute.DashAttack = FActionExcuteData(TagSubsystem->ActionTagSet.ActionDashAttack, EActionPriority::EMedium);
			QuickActionExcute.AttackJump = FActionExcuteData(TagSubsystem->ActionTagSet.ActionJumpAttack, EActionPriority::EHigh); // Jump보다 높게
			QuickActionExcute.ChargeAttack = FActionExcuteData(TagSubsystem->ActionTagSet.ActionChargeAttack, EActionPriority::EMedium); // Jump보다 높게


			QuickActionExcute.KeepDown = FActionExcuteData(TagSubsystem->ActionTagSet.ActionDashAttack, EActionPriority::EHigh);
			QuickActionExcute.Standing = FActionExcuteData(TagSubsystem->ActionTagSet.ActionDashAttack, EActionPriority::EHigh);


			QuickActionExcute.bIsInit = true;
			LOG_V("Action Tag Init");
		}
	}
}

void AHyCharacterBase::CharacterSetup()
{
	// BeginPlay에서 Character를 Setup하는 함수
	MatchArrowComponenLocation();

	CharacterActionTagSetup();

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
			FGameplayTag WeaponSlot = GET_TAG_SUBSYSTEM()->ItemSlotTagSet.SlotWeapon;
			InventorySystemComp->EquipItemBySlot(WeaponSlot);
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
	HyActorComponents.Add(FXSystemComponent);

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
				ArrowCom->bHiddenInGame = false;
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

	if (CollisionSystemComp)
	{
		OnEquipTagChanged.AddDynamic(CollisionSystemComp, &UHyCollisionSystemComponent::SetEquipWeapon);
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
			FVector RelativeLoc = CombatArrowPair.Value->GetRelativeLocation() * GetCapsuleComponent()->GetScaledCapsuleRadius() * 5;
			CombatArrowPair.Value->SetRelativeLocation(RelativeLoc);
		}
	}
}

void AHyCharacterBase::SwitchEquipLayer(const FGameplayTag& InEquipTag)
{
	bool bCombatMode = ECombatMode::ECombat == CharacterStateData.CombatMode;

	CharacterStateData.TagName = InEquipTag;
	OnEquipTagChanged.Broadcast(CharacterStateData.TagName, bCombatMode);
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

bool AHyCharacterBase::GetNextCombatArrowCommand(ECombatDirection& OutArrowDirection)
{
	if (CombatArrowQueue.IsEmpty())
	{
		return false;
	}

	CombatArrowQueue.Dequeue(OutArrowDirection);
	return true;
}

void AHyCharacterBase::SetCombatArrowCommandQueue()
{
	CombatArrowQueue.Empty();

	CombatArrowQueue.Enqueue(ECombatDirection::EBack);
	CombatArrowQueue.Enqueue(ECombatDirection::ERight);
	CombatArrowQueue.Enqueue(ECombatDirection::ELeft);
	CombatArrowQueue.Enqueue(ECombatDirection::EForwardRight);
	CombatArrowQueue.Enqueue(ECombatDirection::EForwardLeft);
	CombatArrowQueue.Enqueue(ECombatDirection::EForward);
}

bool AHyCharacterBase::GetCombatArrowLocation(const ECombatDirection InDirection, FVector& OutCombatArrowLocation)
{
	TObjectPtr<UArrowComponent>* CombatArrowComp = CombatArrowComponentMap.Find(InDirection);
	if (CombatArrowComp && *CombatArrowComp)
	{
		OutCombatArrowLocation = (*CombatArrowComp)->GetComponentLocation();
		return true;
	}

	return false;
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

void AHyCharacterBase::SetWarpingTarget(const FVector& InTargetLocation, const FName& InWarpName)
{
	if (!MotionWarpingComp)
	{
		ERR_V("MotionWarpingComp is not set.");
		return;
	}

	ReleaseWarpingTarget(InWarpName);

	if (InTargetLocation == FVector::ZeroVector)
	{
		ERR_V("InTargetLocation is ZeroVector.");
		return;
	}

	FTransform TargetTransform = GetTransform();
	TargetTransform.SetLocation(InTargetLocation);

	if(InWarpName == FName("Dash"))
	{
		FVector LookVec = InTargetLocation - GetActorLocation();
		FRotator TargetRot = FRotationMatrix::MakeFromX(LookVec).Rotator();
		TargetRot.Pitch = 0;
		FQuat QuatRot = TargetRot.Quaternion();
		TargetTransform.SetRotation(QuatRot);
	}

	MotionWarpingComp->AddOrUpdateWarpTargetFromTransform(InWarpName, TargetTransform);
}

void AHyCharacterBase::ReleaseWarpingTarget(const FName& InWarpName)
{
	if (!MotionWarpingComp)
	{
		ERR_V("MotionWarpingComp is not set.");
		return;
	}

	MotionWarpingComp->RemoveWarpTarget(InWarpName);
}

bool AHyCharacterBase::TriggerActionBlueprint(FActionExcuteData InActionExcuteData, const FString& InContext, bool bCanBeStored)
{
	return TriggerAction(InActionExcuteData, InContext, bCanBeStored);

}

bool AHyCharacterBase::TriggerAction(FGameplayTag& InActionTag, EActionPriority InPriority, const FString& InContext, bool bCanBeStored)
{
	FActionExcuteData ActionData(InActionTag, InPriority);
	return TriggerAction(ActionData, InContext, bCanBeStored);
}

bool AHyCharacterBase::TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext, bool bCanBeStored)
{
	bool bSuccessAction = false;

	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return bSuccessAction;
	}

	if(!InContext.IsEmpty())
	{
		InActionExcuteData.ActionContext = InContext;
	}

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

void AHyCharacterBase::SetStoredAction(FGameplayTag& InActionTag, EActionPriority InPriority, const FString& InContext, bool bForce)
{
	FActionExcuteData ActionData(InActionTag, InPriority);
	SetStoredAction(ActionData, InContext, bForce);
}

void AHyCharacterBase::HandleAction(EActionHandleType InExitType, float BlendOut)
{
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is not set.");
		return;
	}

	if (!FXSystemComponent)
	{
		ERR_V("FXSystemComponent is not set.");
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

	case EActionHandleType::EActionHandle_FX:
		ActionsSystemComp->PlayFX();
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

const bool AHyCharacterBase::IsTargetInRange(const float InRange)
{
	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("Inst is not set.");
		return false;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return false;
	}

	if (IsTargetAvailable())
	{
		if (TObjectPtr<class AHyCharacterBase> TagetCharacter = SpawnManager->GetCharacterByGuid(TargetGuid))
		{
			float Distance = FVector::Dist(TagetCharacter->GetActorLocation(), GetActorLocation());
			return Distance <= InRange;
		}
	}

	return false;
}

const bool AHyCharacterBase::SetCharacterRotationIfInRange(const FVector& InTargetLotation, const float InEnableRange)
{
	FVector LookVector = InTargetLotation - GetActorLocation();

	if (LookVector.Length() < InEnableRange)
	{
		FRotator InputRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
		InputRotation.Pitch = 0;
		SetActorRotation(InputRotation);
		return true;
	}

	return false;
}

const bool AHyCharacterBase::FindNearAttackCollider(const float InExtendRatio)
{
	// 여기서 sweep 체널으로 attack collider find
	// 내것과 내 팀것은 제거하고 상대방것만 찾아야하고..
	// enable 된 것만...


	// 현재 캐릭터의 캡슐 컴포넌트 크기를 가져옴
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (!CapsuleComp)
	{
		return false;
	}

	float CapsuleRadius = CapsuleComp->GetUnscaledCapsuleRadius();
	float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();

	float LargerCapsuleRadius = CapsuleRadius * InExtendRatio;
	float LargerCapsuleHalfHeight = CapsuleHalfHeight * InExtendRatio;

	// 스윕에서 사용할 충돌 캡슐 생성
	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(LargerCapsuleRadius, LargerCapsuleHalfHeight);

	FVector Location = GetActorLocation();

	FRotator Rot = FRotator::ZeroRotator;


	FQuat QuatRot = Rot.Quaternion();
	FCollisionQueryParams InCollisionParams;
	TArray<FHitResult> OutHitResults;

	// 충돌 쿼리 수행
	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHitResults,
		Location,
		Location,
		QuatRot,
		CCHANNEL_HYCHARACTER, // 충돌 채널
		CapsuleShape,         // 크기를 증가시킨 캡슐 모양
		InCollisionParams
	);

	for (FHitResult& Result : OutHitResults)
	{
		if (Result.GetActor())
		{
			LOG_V("Hit Actor : %s", *Result.GetActor()->GetName());
		}
	}

	UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), Location, LargerCapsuleHalfHeight, LargerCapsuleRadius, QuatRot, FColor::Blue, 1.0f, 1.f);

	return true;
}

void AHyCharacterBase::SetAirHitWarpLocation(const FVector& InLocation)
{
	CharacterCombatDataSet.AirHitLocation = InLocation;


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

	if (!IsCanAction(EKeyInput::IA_Attack))
	{
		return;
	}

	if (IsCombatMode())
	{
		// 공중에서는 타겟 변경 못하도록
		if(GET_TAG_SUBSYSTEM()->IsInAirAction(GetCurAction()) == false)
		{
			FindTarget();
		}

		TriggerAttackAction();
	}
	else
	{
		FString Context = TEXT("Auto");
		TriggerAction(QuickActionExcute.Equip, Context);
	}
}

void AHyCharacterBase::InputChargeAttack(const FInputActionValue& Value)
{
	LOG_I;
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

	if (!IsCanAction(EKeyInput::IA_Attack))
	{
		return;
	}

	if (IsCombatMode())
	{
		if (GET_TAG_SUBSYSTEM()->IsChargeAttackAction(GetCurAction()) == false)
		{
			FindTarget();
			TriggerAction(QuickActionExcute.ChargeAttack, "", true);
		}
	}
	else
	{
		FString Context = TEXT("Auto");
		TriggerAction(QuickActionExcute.Equip, Context);
	}
}

void AHyCharacterBase::InputAirStartAttack(const FInputActionValue& Value)
{
	LOG_I;
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

	if (!IsCanAction(EKeyInput::IA_RAttack))
	{
		return;
	}

	if (IsCombatMode())
	{
		FindTarget();

		LOG_V("%s", *GetActorLocation().ToString());


		// 타겟이 있으면 타겟에 Dash > AirStartAttack
		if (IsTargetAvailable())
		{
			TriggerAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionDash, EActionPriority::EMedium, "AirStart");
		}
		else
		{
			// 타겟이 없으면 AirStartAttack ( 제자리 )
			TriggerAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionAirStartAttacking, EActionPriority::EMedium);
		}

	}
}

void AHyCharacterBase::TriggerAttackAction()
{
	if (!HyAnimInstance)
	{
		ERR_V("HyAnimInstance is not set.");
		return;
	}

	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	UHyTagSubsystem* HyTagSubSystem = GET_TAG_SUBSYSTEM();
	if(!HyTagSubSystem)
	{
		ERR_V("HyTagSubSystem is not set.");
		return;
	}

	UHyInst* Inst = UHyInst::Get();
	if(!Inst)
	{
		ERR_V("Inst is not set.");
		return;
	}	

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if(!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return;
	}

	if (!ActionsSystemComp)
	{
		ERR_V("ActionSetComponent is not set.");
		return;
	}

	if (HyTagSubSystem->IsStandAction(GetCurAction()))
	{
		// JumpAttack 
		if (HyAnimInstance->GetJumpData().bIsInAir)
		{
			TriggerAction(QuickActionExcute.AttackJump, FString());
		}
		else
		{
			if (!GET_TAG_SUBSYSTEM()->IsDashAttackAction(GetCurAction()))
			{
				bool bIsComboAttack = GET_TAG_SUBSYSTEM()->IsComboAttackAction(GetCurAction());
				// (콤보 어택 && 마지막 인덱스) or 콤보 어택이 아닌경우
				if (bIsComboAttack && ActionsSystemComp->IsLastMonstageSection() || !bIsComboAttack)
				{
					TriggerAction(QuickActionExcute.DashAttack, FString(), true);
					return;
				}
			}

			// Dash Atack이 아니면 콤보어택
			TriggerAction(QuickActionExcute.Attack, FString(), true);
		}
	}
	else if (HyTagSubSystem->IsInAirAction(GetCurAction()))
	{
		TriggerAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionAirAttacking, EActionPriority::EMedium, "", true);
	}
}

void AHyCharacterBase::InputMove(const FInputActionValue& Value)
{
	if (!Controller)
	{
		ERR_V("No Controller");
		return;
	}

	if (!ActionsSystemComp)
	{
		ERR_V("No ActionsSystemComp");
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

	// attack stop 가능 구간이 넘어선 경우
	if (GET_TAG_SUBSYSTEM()->IsAttackAction(GetCurAction()))
	{
		HandleAction(EActionHandleType::EActionHandle_Stop);
	}

	TriggerAction(QuickActionExcute.Move);

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
	if (!ActionsSystemComp)
	{
		ERR_V("ActionsSystemComp is invalid");
		return;
	}

	FGameplayTag CurActionTag = ActionsSystemComp->GetPerformingActionTag();

	if (UHyTagSubsystem* TagSubsystem = GET_TAG_SUBSYSTEM())
	{
		if (TagSubsystem->ActionTagSet.ActionMove == CurActionTag)
		{
			HandleAction(EActionHandleType::EActionHandle_Stop);
		}
	}

}

void AHyCharacterBase::InputJump(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Jump))
	{
		return;
	}

	TriggerAction(QuickActionExcute.Jump);

}

void AHyCharacterBase::InputLook(const FInputActionValue& Value)
{
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
	if (!InventorySystemComp)
	{
		ERR_V("InventorySystemComp is not set.");
		return;
	}

	FString Context = TEXT("Auto");
	TriggerAction(QuickActionExcute.UnEquip, Context);

	//FGameplayTag WeaponSlot = GET_TAG_SUBSYSTEM()->ItemSlotTagSet.SlotWeapon;
	//if (InventorySystemComp->IsEquippedSlot(WeaponSlot))
	//{
	//	InventorySystemComp->UnEquipItemBySlot(WeaponSlot);
	//}
	//else
	//{
	//	InventorySystemComp->EquipItemBySlot(WeaponSlot);
	//}
}

void AHyCharacterBase::InputSprint(const FInputActionValue& Value)
{
	LOG_I;

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
	LOG_I;

	if (!HyCharacterMovement)
	{
		ERR_V("HyCharacterMovement is not set.");
		return;
	}

	if (!HyCharacterMovement->IsDefaultLocomotionState())
	{
		HyCharacterMovement->SetDefaultLocomotionState();
	}
}

void AHyCharacterBase::InputDodge(const FInputActionValue& Value)
{
	LOG_I;
	if (HyAnimInstance == nullptr)
	{
		ERR_V("HyAnimInstance is null");
		return;
	}

	FString ActionContext;
	switch (HyAnimInstance->GetVelocityData().SpeedDirection)
	{
	case EHyDirection::Front:
		ActionContext = TEXT("Front");
		break;
	case EHyDirection::Back:
		ActionContext = TEXT("Back");
		break;
	case EHyDirection::Left:
		ActionContext = TEXT("Left");
		break;
	case EHyDirection::Right:
		ActionContext = TEXT("Right");
		break;
	default:
		break;
	}
	// slide, avoid 등등..

	// input direction


	if (IsCombatMode())
	{
		TriggerAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionAvoid, EActionPriority::EMedium, ActionContext);

		FindNearAttackCollider(5);
	}
	else
	{
		TriggerAction(GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSlide, EActionPriority::EMedium, ActionContext);
	}
}

void AHyCharacterBase::InputCrouch(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Crouch))
	{
		return;
	}

	TriggerAction(QuickActionExcute.Crouching);
}

void AHyCharacterBase::InputSkill1(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Skill1))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSkill1;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
}

void AHyCharacterBase::InputSkill2(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Skill2))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSkill2;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
}

void AHyCharacterBase::InputSkill3(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Skill3))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSkill3;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
}

void AHyCharacterBase::InputSkill4(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Skill4))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSkill4;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
}

void AHyCharacterBase::InputSkill5(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Skill5))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionSkill5;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
}

void AHyCharacterBase::InputUlti(const FInputActionValue& Value)
{
	if (!IsCanAction(EKeyInput::IA_Ulti))
	{
		return;
	}

	const FGameplayTag ActionTag = GET_TAG_SUBSYSTEM()->ActionTagSet.ActionUlti;

	FActionExcuteData ChangeActionData = FActionExcuteData(ActionTag, EActionPriority::EMedium);
	TriggerAction(ChangeActionData);
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

void AHyCharacterBase::NotifyAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet)
{
	UHyInst* Inst = UHyInst::Get();
	if (!Inst)
	{
		ERR_V("Inst is not set.");
		return;
	}

	UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
	if (!SpawnManager)
	{
		ERR_V("SpawnManager is not set.");
		return;
	}

	if (InAttackCollisionSet.SettingType == EAttackCollisionSetting::ACS_TargetAttack)
	{
		if (IsTargetAvailable())
		{
			if (TObjectPtr<class AHyCharacterBase> TargetCharacter = SpawnManager->GetCharacterByGuid(TargetGuid))
			{
				FVector AtackDirection = TargetCharacter->GetActorLocation() - GetActorLocation();

				FHyDamageEvent DamageEvent;
				FHitResult HitResult;
				DamageEvent.HitTag = InAttackCollisionSet.TagName;
				DamageEvent.AttackDirection = AtackDirection.GetSafeNormal2D();
				TargetCharacter->TakeDamage(100, DamageEvent, GetController(), this);
			}
		}
	}
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
		ERR_V("Character is already dead");
		return 0.0f;
	}

	if (!DamageCauser)
	{
		ERR_V("DamageCauser is invalid");
		return 0.0f;
	}



	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	if (DamageEvent.GetTypeID() == FHyDamageEvent::ClassID)
	{
		const FHyDamageEvent& HyDamageEvent = static_cast<const FHyDamageEvent&>(DamageEvent);


		const FGameplayTag HitActionTag = GET_TAG_SUBSYSTEM()->GetActionTypeByDamageType(HyDamageEvent.HitTag, GetCurAction());

		KeepDownTime = HyDamageEvent.DownTime;

		// Action
		LastAttackDirection = HyDamageEvent.AttackDirection;
		FActionExcuteData ChangeActionData = FActionExcuteData(HitActionTag, EActionPriority::EHigh, HyDamageEvent.ActionContext);
		TriggerAction(ChangeActionData);
		
		AHyCharacterBase* DealerCharacter = Cast<AHyCharacterBase>(DamageCauser);
		if (DealerCharacter)
		{
			TargetGuid = DealerCharacter->GetMyGuidRef();
			OnDamageReceived.Broadcast(HyDamageEvent, DealerCharacter->GetMyGuidRef());

			if (TObjectPtr<UHyInventorySystemComponent> InvenComp = DealerCharacter->GetInventorySystemComp())
			{
				if (TObjectPtr<AHyWeapon> Waepon = InvenComp->GetEquippedWeapon())
				{
					Waepon->ActiveTrail(true, AttackTrailType);
				}
			}
		}

		// DamageFont
		//if (FXComponent)
		//{
		//	FXComponent->SpawnDamageText(DamageAmount, HyDamageEvent.DamageType);
		//}
	}

	return Damage;
}

void AHyCharacterBase::SetCharacterCollisionEnable(bool bEnable)
{
	// Pawn하고만 충돌 체크 금지
	if(bEnable)
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	}
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

	
	if(GET_TAG_SUBSYSTEM()->IsDeadAction(ActionsSystemComp->GetPerformingActionTag()))
	{
		return true;
	}

	return false;
}

const bool AHyCharacterBase::IsCanAction(EKeyInput InKeyAction) const
{
	bool bRes = false;


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
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);
		if (!bRes)
		{
			// 전투모드인 경우
			// 점프 or Attack이라면 인풋 허용
			if (IsCombatMode())
			{
				if (GET_TAG_SUBSYSTEM()->IsJumpAction(CurActionTag) || GET_TAG_SUBSYSTEM()->IsAttackAction(CurActionTag))
				{
					bRes = true;
				}
			}

		}
		break;
	case EKeyInput::IA_RAttack:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);
		if (!bRes)
		{
			// 전투모드인 경우
			if (IsCombatMode())
			{
				if (GET_TAG_SUBSYSTEM()->IsAttackAction(CurActionTag))
				{
					bRes = true;
				}
			}

		}
		break;
	case EKeyInput::IA_Equip:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Skill1:
	case EKeyInput::IA_Skill2:
	case EKeyInput::IA_Skill3:
	case EKeyInput::IA_Skill4:
	case EKeyInput::IA_Skill5:
	case EKeyInput::IA_Ulti:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Jump:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);

		break;
	case EKeyInput::IA_Move:
	{
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);
		if (!bRes)
		{
			if (GET_TAG_SUBSYSTEM()->IsAttackAction(CurActionTag))
			{
				if (CompareCurrentPriority(EActionPriority::ENone))
				{
					bRes = true;
				}
			}
		}
	}
		break;
	case EKeyInput::IA_Look:

		break;
	case EKeyInput::IA_Sprint:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);

		break;

	case EKeyInput::IA_Crouch:
		bRes = GET_TAG_SUBSYSTEM()->IsNormalAction(CurActionTag);
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
		if (DevSetting->IsDebugDrawWidget())
		{
			DebugRenderWidget();
		}
		else
		{
			if (SCharacterDebugWidget.IsValid())
			{
				SCharacterDebugWidget->SetVisibility(EVisibility::Hidden);
			}
		}

		if (DevSetting->IsDebugDrawMovement())
		{
			DebugDrawMovement();
		}

		if (DevSetting->IsDebugDrawCollision())
		{
			DebugDrawTargetHitDirection();

			for (auto& CombatArrowPair : CombatArrowComponentMap)
			{
				if (CombatArrowPair.Value)
				{
					CombatArrowPair.Value->bHiddenInGame = false;
					CombatArrowPair.Value->SetVisibility(true);
				}
			}
		}
		else
		{
			for (auto& CombatArrowPair : CombatArrowComponentMap)
			{
				if (CombatArrowPair.Value)
				{
					CombatArrowPair.Value->bHiddenInGame = true;
					CombatArrowPair.Value->SetVisibility(false);
				}
			}
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
		SCharacterDebugWidget->SetVisibility(EVisibility::Visible);

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

void AHyCharacterBase::DebugDrawMovement()
{
	if (!HyAnimInstance)
	{
		ERR_V("HyAnimInstance is not set.");
		return;
	}


	float Height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + (CharacterInputData.InputDirection * 50);

	// Forward	
	UHyCoreFunctionLibrary::DrawArrow(GetWorld(), Start, Start + GetActorForwardVector() * 50.f, 30, FLinearColor::Black);

	// Input Direction
	Start.Z += Height * 0.5f;
	End.Z += Height * 0.5f;
	UHyCoreFunctionLibrary::DrawArrow(GetWorld(), Start, End);

	Start = GetActorLocation();
	Start.Z += Height;

	// Acceleration Ratio
	const FAnimationAccelerationData& AccelerationData = HyAnimInstance->GetAccelerationData();
	End = GetActorLocation() + AccelerationData.NormalizedAccel * AccelerationData.AccelerationRatio * 100;
	End.Z += Height;
	UHyCoreFunctionLibrary::DrawArrow(GetWorld(), Start, End, 30, FLinearColor::Yellow);

	// Velocity Ratio
	const FAnimationVelocityData& VelocityData = HyAnimInstance->GetVelocityData();
	End = GetActorLocation() + VelocityData.NormalizedSpeed * VelocityData.WorldSpeed2D.GetSafeNormal2D() * 100;
	Start.Z += 5;
	End.Z += Height + 5;
	UHyCoreFunctionLibrary::DrawArrow(GetWorld(), Start, End, 30, FLinearColor::Blue);



}

void AHyCharacterBase::DebugDrawTargetHitDirection()
{
	if (IsTargetAvailable())
	{
		UHyInst* Inst = UHyInst::Get();
		if (!Inst)
		{
			ERR_V("Inst is not set.");
			return;
		}

		UHySpawnManager* SpawnManager = Inst->GetManager<UHySpawnManager>();
		if (!SpawnManager)
		{
			ERR_V("SpawnManager is not set.");
			return;
		}

		if (TObjectPtr<class AHyCharacterBase> TargetCharacter = SpawnManager->GetCharacterByGuid(TargetGuid))
		{
			FVector AttackDirection = TargetCharacter->GetActorLocation() - GetActorLocation();
			AttackDirection.Normalize();

			// 상대방의 로컬 좌표계에서의 공격 방향 계산
			//FVector LocalAttackDirection = TargetCharacter->GetActorTransform().InverseTransformVector(AttackDirection);
			FVector TargetForward = TargetCharacter->GetActorForwardVector();
			float DotProduct = FVector::DotProduct(AttackDirection, TargetForward);
			FVector CrossProduct = FVector::CrossProduct(TargetForward, AttackDirection);

			//if(GET_TAG_SUBSYSTEM()->IsMonsterCharacter(TargetCharacter->GetCharacterTypeTag()))
			//{
			//	LOG_V("DotProduct %f CrossProduct Z %f", DotProduct, CrossProduct.Z);
			//}
			UHyCoreFunctionLibrary::DrawArrow(GetWorld(), TargetCharacter->GetActorLocation(), TargetCharacter->GetActorLocation() + AttackDirection * 100, 10, FLinearColor::Red);

		}


	}
}

