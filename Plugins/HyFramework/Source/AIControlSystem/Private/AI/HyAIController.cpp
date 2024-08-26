// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HyAIController.h"

//#include "Interface/ActionsCharacterInterface.h"

#include "Game/HyGameInstance.h"
#include "Manager/HySpawnManager.h"


#include "Actors/Character/HyCharacterBase.h"
//#include "GameFramework/Character.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <BehaviorTree/Blackboard/BlackboardKeyType_Bool.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Enum.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Int.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>

#include <Navigation/CrowdFollowingComponent.h>
#include <Navigation/PathFollowingComponent.h>


#include "HyCoreMacro.h"



AHyAIController::AHyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
}

void AHyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!InPawn)
	{
		ERR_V("InPawn is nullptr");
		return;
	}

	CharacterOwner = Cast<AHyCharacterBase>(InPawn);
	if (!CharacterOwner)
	{
		ERR_V("CharacterOwner is nullptr");
		return;
	}


	if (!BehaviorTree)
	{
		ERR_V("BehaviorTree is nullptr");
		return;
	}

	//OwnerActionsInterface = Cast<IActionsCharacterInterface>(InPawn);
	//if (!OwnerActionsInterface)
	//{
	//	ERR_V("OwnerActionsInterface is nullptr");
	//	return;
	//}

	UBlackboardData* const BBData = BehaviorTree->BlackboardAsset;
	if (BBData == nullptr)
	{
		ERR_V("BlackboardData is nullptr");
		return;
	}

	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}

	BlackboardComponent->InitializeBlackboard(*BBData);
	Blackboard = BlackboardComponent;
	HomeLocation = InPawn->GetActorLocation();

	BlackBoardKeyBindings();



	CharacterOwner->OnDamageReceived.AddDynamic(this, &AHyAIController::HandleOwnerCharacterDamaged);


	BehaviorTreeComponent->StartTree(*BehaviorTree);

}

void AHyAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void AHyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHyAIController::BlackBoardKeyBindings()
{
	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}


	// Fetch the Keys
	targetActorKey = BlackboardComponent->GetKeyID("TargetActor");
	targetPointLocationKey = BlackboardComponent->GetKeyID("TargetLocation");
	targetActorDistanceKey = BlackboardComponent->GetKeyID("TargetActorDistance");
	targetDistanceKey = BlackboardComponent->GetKeyID("TargetLocationDistance");
	isPausedKey = BlackboardComponent->GetKeyID("Paused");
	aiStateKey = BlackboardComponent->GetKeyID("AIState");
	homeDistanceKey = BlackboardComponent->GetKeyID("HomeDistance");

	BlackBoardKeyInit();
}

void AHyAIController::BlackBoardKeyInit()
{
	if (!BlackboardComponent)
	{
		ERR_V("BlackboardComponent is nullptr");
		return;
	}

	BlackboardComponent->SetValue<UBlackboardKeyType_Float>(targetDistanceKey, MAX_FLT);
	BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(targetPointLocationKey, HomeLocation);
	BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(isPausedKey, false);
	BlackboardComponent->SetValue<UBlackboardKeyType_Enum>(aiStateKey, static_cast<uint8>(EAIState::EWait));
}

void AHyAIController::SetTarget(AActor* InTarget)
{
	if (!InTarget)
	{
		SetAIStateBBK(EAIState::EWait);
	}
	else
	{
		SetAIStateBBK(EAIState::ECombat);
	}

	SetTargetActorBBK(InTarget);
}

void AHyAIController::HandleOwnerCharacterDamaged(const FHyDamageEvent& InDamageEvent, const FGuid& InDealerGuid)
{
	if (InDamageEvent.DamageType == EHyDamageType::EHyDamage_Miss)
	{
		return;
	}

	// 타겟 교체
	if (UHyInst* HyGameInst = UHyInst::Get())
	{
		if (UHySpawnManager* SpawnManager = HyGameInst->GetManager<UHySpawnManager>())
		{
			if (TObjectPtr<class AHyCharacterBase> Dealer = SpawnManager->GetCharacterByGuid(InDealerGuid))
			{
				SetTarget(Dealer);
			}
		}
	}
}

void AHyAIController::SetTargetActorBBK(AActor* InTarget)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Object>(targetActorKey, InTarget);
	}

}

void AHyAIController::SetTargetLocationBBK(const FVector& InTargetLocation)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Vector>(targetPointLocationKey, InTargetLocation);
	}
}


void AHyAIController::SetTargetDistanceBBK(float InDistance)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Float>(targetDistanceKey, InDistance);
	}
}

void AHyAIController::SetHomeDistanceBBK(float InDistance)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Float>(homeDistanceKey, InDistance);
	}
}



void AHyAIController::SetAIStateBBK(EAIState InaiState)
{
	if (GetAIStateBBK() == InaiState)
	{
		return;
	}

	if (!BlackboardComponent)
	{
		return;
	}

	switch (InaiState)
	{
	case EAIState::EPatrol:
		SetTargetLocationBBK(HomeLocation);
		break;
	case EAIState::ECombat:
		if (AActor* Target = GetTargetActorBBK())
		{
			SetTargetLocationBBK(Target->GetActorLocation());
		}
		break;
	case EAIState::EReturnHome:
		SetTargetLocationBBK(HomeLocation);
		break;
	case EAIState::EWait:
		SetTargetLocationBBK(FVector::ZeroVector);
		break;
	default:
		break;
	}

	BlackboardComponent->SetValue<UBlackboardKeyType_Enum>(aiStateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(InaiState));
}

AActor* AHyAIController::GetTargetActorBBK() const
{
	if (BlackboardComponent)
	{
		AActor* targetActor = Cast<AActor>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(targetActorKey));
		return targetActor;
	}
	return nullptr;
}

const FVector AHyAIController::GetTargetLocationBBK() const
{
	if (BlackboardComponent)
	{
		return BlackboardComponent->GetValue<UBlackboardKeyType_Vector>(targetPointLocationKey);
	}

	return FVector();
}

const float AHyAIController::GetHomeDistanceBBK() const
{
	if (BlackboardComponent)
	{
		return BlackboardComponent->GetValue<UBlackboardKeyType_Float>(homeDistanceKey);
	}

	return -1.f;
}

EAIState AHyAIController::GetAIStateBBK() const
{
	if (BlackboardComponent)
	{
		return static_cast<EAIState>(BlackboardComponent->GetValue<UBlackboardKeyType_Enum>(aiStateKey));
	}

	return EAIState::EWait;
}
