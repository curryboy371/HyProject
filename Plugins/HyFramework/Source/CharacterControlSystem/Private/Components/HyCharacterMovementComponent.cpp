// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyCharacterMovementComponent.h"

#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"

#include "Engine/World.h"
#include <Components/SkeletalMeshComponent.h>


#include "Animation/HyAnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


#include "HyCoreMacro.h"



UHyCharacterMovementComponent::UHyCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	GroundDistance = 0.0f;


    FCharacterMovementData CharacterMovementData;
    CharacterMovementData.MaxWalkSpeed = 0.0f;
    LocomotionStates.Add(FLocomotionState(ELocomotionState::EIdle, CharacterMovementData));

    CharacterMovementData.MaxWalkSpeed = 300.0f;
    LocomotionStates.Add(FLocomotionState(ELocomotionState::EWalk, CharacterMovementData));

    CharacterMovementData.MaxWalkSpeed = 600.f;
    LocomotionStates.Add(FLocomotionState(ELocomotionState::EJog, CharacterMovementData));

    CharacterMovementData.MaxWalkSpeed = 900.f;
    LocomotionStates.Add(FLocomotionState(ELocomotionState::ESprint, CharacterMovementData));


    CurLocomotionState = ELocomotionState::EIdle;
    CurMovestance = EMovementStance::EIdle;


    // Crouch 허용
    GetNavAgentPropertiesRef().bCanCrouch = true;

}

void UHyCharacterMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    SetOwnerReference();

    SetLocomotionState(DefaultState);
}

void UHyCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateLocomotion();

}

void UHyCharacterMovementComponent::SetOwnerReference()
{
    if (CharacterOwner && CharacterOwner->GetMesh())
    {
        AnimInstance = Cast<UHyAnimInstance>(CharacterOwner->GetMesh()->GetAnimInstance());
    }

    if (!AnimInstance)
    {
        ERR_V("AnimInstance is nullptr");
    }
}

void UHyCharacterMovementComponent::UpdateLocomotion()
{
    if (!AnimInstance)
    {
        ERR_V("AnimInstance is nullptr");
    }

    if (!CharacterOwner) 
    {
        ERR_V("CharacterOwner is nullptr");
        return;
    }

    if (!IsFalling() && !AnimInstance->IsAnyMontagePlaying()) 
    {
        if (GetGroundMovementMode() == EMovementMode::MOVE_Walking)
        {
            for (int i = 0; i < LocomotionStates.Num() - 1; ++i) 
            {
                const float Speed = CharacterOwner->GetVelocity().Size();

                if (FMath::IsNearlyZero(Speed) && CurLocomotionState != ELocomotionState::EIdle) 
                {
                    // Idle이 아닌데, Velocity가 0이면 Idle로 변경
                    HandleStateChanged(ELocomotionState::EIdle);
                }
            
                else if (LocomotionStates[i + 1].State != CurLocomotionState \
                    && Speed > LocomotionStates[i].GetMaxSpeed() + 5.f \
                    && Speed <= LocomotionStates[i + 1].GetMaxSpeed() + 5.f)
                {
                    // 다음 속도 구간에 들어가면 상태 변경
                    HandleStateChanged(LocomotionStates[i + 1].State);
                }
            }
            
            if (CurLocomotionState == ELocomotionState::ESprint) 
            {
                // Sprint로 전환시에는 각도가 SprintDirectionCone을 벗어나면 Jog로 격하
                const float Direction = AnimInstance->GetVelocityData().Direction;
                if (FMath::Abs(Direction) > SprintDirectionCone) 
                {
                    SetLocomotionState(ELocomotionState::EJog);
                }
            }
        }
        else 
        {
            // 지면이 아닌 경우 Idle로 변경
            SetLocomotionState(ELocomotionState::EIdle);
        }
    }
}

void UHyCharacterMovementComponent::CalcGroundDistance()
{
    if (!CharacterOwner) 
    {
        ERR_V("CharacterOwner is nullptr");
    }

    if (MovementMode == EMovementMode::MOVE_Walking)
    {
        GroundDistance = 0.0f;
    }
    else 
    {
        if (const UCapsuleComponent* CapsuleComp = CharacterOwner->GetCapsuleComponent())
        {
            const float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();
            const ECollisionChannel CollisionChannel = (UpdatedComponent ? UpdatedComponent->GetCollisionObjectType() : ECC_Pawn);
            const FVector TraceStart(CharacterOwner->GetActorLocation());
            const FVector TraceEnd(TraceStart.X, TraceStart.Y, (TraceStart.Z - GroundTraceDistance - CapsuleHalfHeight));

            FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ACFCharacterMovementComponent_GetGroundInfo), false, CharacterOwner);
            FCollisionResponseParams ResponseParam;
            InitCollisionParams(QueryParams, ResponseParam);

            FHitResult HitResult;
            GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, QueryParams, ResponseParam);

            GroundDistance = GroundTraceDistance;

            // NavingWalking 상태에서는 GroundDistance 0
            if (MovementMode == MOVE_NavWalking) 
            {
                GroundDistance = 0.0f;
            }
            else if (HitResult.bBlockingHit) 
            {
                //지면과의 거리를 계산
                // 충돌 지점까지의 - 캡슐 절반
                GroundDistance = FMath::Max((HitResult.Distance - CapsuleHalfHeight), 0.0f);
            }

        }
		else 
		{
			ERR_V("CapsuleComponent is nullptr");
		}


    }
}

void UHyCharacterMovementComponent::SetLocomotionState(ELocomotionState InState)
{
    if (TargetLocomotionState.State == InState)
    {
        return;
    }

    if (FLocomotionState* LocomotionState = LocomotionStates.FindByKey(InState)) // operator로 key값 사용
    {
        TargetLocomotionState = *(LocomotionState);
    
        MaxWalkSpeed = TargetLocomotionState.CharacterMovementData.MaxWalkSpeed;
        MaxAcceleration = TargetLocomotionState.CharacterMovementData.MaxAcceleration;
        BrakingDecelerationWalking = TargetLocomotionState.CharacterMovementData.BrakingDeceleration;
        BrakingFrictionFactor = TargetLocomotionState.CharacterMovementData.BrakingFrictionFactor;
        BrakingFriction = TargetLocomotionState.CharacterMovementData.BrakingFriction;
        bUseSeparateBrakingFriction = TargetLocomotionState.CharacterMovementData.UseSeparateBrakingFriction;
    
        OnTargetLocomotionStateChanged.Broadcast(InState);
    }
    else 
    {
        ERR_V("Locomotion State inexistent");
    }
}

void UHyCharacterMovementComponent::SetDefaultLocomotionState()
{
    SetLocomotionState(DefaultState);
}

void UHyCharacterMovementComponent::HandleStateChanged(ELocomotionState InChangeState)
{
    if (CurLocomotionState == InChangeState)
    {
        return;
    }

    CurLocomotionState = InChangeState;
    OnLocomotionStateChanged.Broadcast(InChangeState);
}

void UHyCharacterMovementComponent::AccelerateToNextState()
{
    const int32 Actualindex = LocomotionStates.IndexOfByKey(CurLocomotionState);

    if (LocomotionStates.IsValidIndex(Actualindex + 1))
    {
        SetLocomotionState(LocomotionStates[Actualindex + 1].State);
    }
}

void UHyCharacterMovementComponent::BrakeToPreviousState()
{
    const int32 Actualindex = LocomotionStates.IndexOfByKey(CurLocomotionState);

    if (LocomotionStates.IsValidIndex(Actualindex - 1))
    {
        SetLocomotionState(LocomotionStates[Actualindex - 1].State);
    }
}

const float UHyCharacterMovementComponent::GetCharacterMaxStateSpeed(ELocomotionState InState)
{
    FLocomotionState* LocomotionState = LocomotionStates.FindByKey(InState);
    if (LocomotionState)
    {
        return LocomotionState->CharacterMovementData.MaxWalkSpeed;
    }

    return 0.0f;
}
