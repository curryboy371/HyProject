// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"

#include "Animation/HyAnimEquipLayer.h"
#include "Animation/HyAnimLayer.h"

#include "HyCoreMacro.h"



#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "KismetAnimationLibrary.h"
#include <Animation/AimOffsetBlendSpace1D.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include <TimerManager.h>



UHyAnimInstance::UHyAnimInstance()
{


}

void UHyAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (!IsEditorBlueprint())
    {
        SetCharacterReferences();
    }
}

void UHyAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();


}

void UHyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    // Animation Tread는 별도로 동작하니 Animinstace의 변수 업데이트는 threadsafe하게 update
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    // 에디트 블루프린트에서는 실행안함
    if (IsEditorBlueprint())
    {
        return;
    }

    if (AnimationUpdateSwitch.bUpdateMovementData)
    {
        UpdateStateData(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateLocationData)
    {
        UpdateLocation(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateRotationData)
    {
        UpdateRotation(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateSpeedData)
    {
        UpdateVelocity(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateAccelerationData)
    {
        UpdateAcceleration(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateAimData)
    {
        UpdateAimData(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateJumpData)
    {
        UpdateJump(DeltaSeconds);
    }
    if (AnimationUpdateSwitch.bUpdateLeaningData)
    {
        UpdateLeaning(DeltaSeconds);
    }

}

bool UHyAnimInstance::IsEditorBlueprint()
{
    if (TryGetPawnOwner() && TryGetPawnOwner()->GetWorld() && TryGetPawnOwner()->GetWorld()->IsGameWorld())
	{
        return !TryGetPawnOwner()->GetWorld()->IsGameWorld();
	}

    return true;
}

void UHyAnimInstance::SetCharacterReferences()
{
    CharacterOwner = Cast<ACharacter>(TryGetPawnOwner());
    if (CharacterOwner) 
    {
        CharacterMovementComp = Cast<UCharacterMovementComponent>(CharacterOwner->GetCharacterMovement());
        
        if(!CharacterMovementComp)
        {
            ERR_V("Owner doesn't have ACharacterMovement Comp!!!!");
        }
    }
    else
    {
        ERR_V("Owner is not ACharacter");
    }
}

void UHyAnimInstance::SetEquipLayer(const FGameplayTag& InEquipTag)
{
    if (FHyAnimEquipLayerSet* FindEquipLayer = EquipLayers.FindByKey(InEquipTag))
    {
        if (FindEquipLayer->EquipLayer)
        {
            if (CurEquipLayerInst)
            {
                CurEquipLayerInst->OnDeactivated(); // Layer Deactive
            }

            CharacterStateData.TagName = InEquipTag;
            CharacterStateData.SetCombatMode(CharacterDefaultTagSet.CombatEquipTag == CharacterStateData.TagName);

            LinkAnimClassLayers(FindEquipLayer->EquipLayer);

            CurEquipLayerInst = Cast<UHyAnimEquipLayer>(GetLinkedAnimLayerInstanceByClass(FindEquipLayer->EquipLayer));
            if (CurEquipLayerInst)
            {
                CurEquipLayerInst->OnActivated(); // Layer Active
            }
        }
    }
    else
    {
        ERR_V("EquipLayer is not found");
    }
}

void UHyAnimInstance::UpdateLeaning(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateLocation(const float& DeltaSeconds)
{
    if (!CharacterOwner)
    {
        ERR_V("CharacterOwner is nullptr");
		return;
    }

    LocationData.DisplacementDelta = UKismetMathLibrary::VSizeXY(CharacterOwner->GetActorLocation() - LocationData.OwnerLocation);
    LocationData.OwnerLocation = CharacterOwner->GetActorLocation();
    LocationData.Displacement = UKismetMathLibrary::SafeDivide(LocationData.DisplacementDelta, DeltaSeconds);
}

void UHyAnimInstance::UpdateRotation(const float& DeltaSeconds)
{
    if (!CharacterOwner)
    {
        ERR_V("CharacterOwner is nullptr");
        return;
    }

    RotationData.PreviousRotation = RotationData.OwnerRotation;
    RotationData.OwnerRotation = CharacterOwner->GetActorRotation();
    RotationData.YawDelta = RotationData.OwnerRotation.Yaw - RotationData.PreviousRotation.Yaw;
    RotationData.YawSpeed = UKismetMathLibrary::SafeDivide(RotationData.YawDelta, DeltaSeconds);

    //const FRotator RotDelta = UKismetMathLibrary::NormalizedDeltaRotator(RotationData.OwnerRotation, RotationData.PreviousRotation);
    //const float Turn = RotDelta.Yaw;
    //TurnRate = FMath::FInterpTo(TurnRate, Turn, DeltaSeconds, TurnRateSmoothing);
}

void UHyAnimInstance::UpdateVelocity(const float& DeltaSeconds)
{
    //VelocityData.LastSpeedDirectionWithOffset = SpeedDirectionWithOffset;
    //VelocityData.LastSpeedDirection = VelocityData.SpeedDirection;

    VelocityData.PreviousSpeed = VelocityData.Speed;
    //VelocityData.bWasMoving = !FMath::IsNearlyZero(VelocityData.Speed, VelocityData.IsMovingSpeedThreshold);
    VelocityData.WorldSpeed = CharacterOwner->GetVelocity();
    VelocityData.Speed = VelocityData.WorldSpeed.Size();
    VelocityData.WorldSpeed2D = VelocityData.WorldSpeed * FVector(1.f, 1.f, 0.f);
    VelocityData.LocalSpeed2D = RotationData.OwnerRotation.UnrotateVector(VelocityData.WorldSpeed2D);
    VelocityData.Direction = UKismetAnimationLibrary::CalculateDirection(VelocityData.WorldSpeed2D, RotationData.OwnerRotation);
    VelocityData.DirectionWithOffset = VelocityData.Direction - RotationData.YawOffset;
    //VelocityData.SpeedDirection = GetDirectionFromAngle(Direction, LastSpeedDirection, bWasMoving);
    //SpeedDirectionWithOffset = GetDirectionFromAngle(DirectionWithOffset, LastSpeedDirectionWithOffset, bWasMoving);
    //VelocityData.NormalizedSpeed = UKismetMathLibrary::SafeDivide(VelocityData.Speed, CharacterMovementComp->GetCharacterMaxSpeed());
    //if (IsLocalPlayer()) 
    //{
    //    DeltaInputDirection = UKismetAnimationLibrary::CalculateDirection(MovementComp->GetLastInputVector(), CharacterOwner->GetActorRotation());
    //}
    //else {
    //    // We don't have inputs on server
    //    DeltaInputDirection = DirectionWithOffset;
    //}
    //bIsMoving = !FMath::IsNearlyZero(Speed, IsMovingSpeedThreshold);
    //if (bIsSwimming) {
    //    NormalizedSwimSpeed = UKismetMathLibrary::SafeDivide(Speed, MovementComp->MaxSwimSpeed);
    //}
}

void UHyAnimInstance::UpdateAimData(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateAcceleration(const float& DeltaSeconds)
{
    if (!CharacterMovementComp)
    {
        ERR_V("CharacterMovementComp is nullptr");
		return;
    }
    
    AccelerationData.Acceleration = CharacterMovementComp->GetCurrentAcceleration().Size();
    AccelerationData.Acceleration2D = CharacterMovementComp->GetCurrentAcceleration() * FVector(1.f, 1.f, 0.f);
    AccelerationData.LocalAccel2D = RotationData.OwnerRotation.UnrotateVector(AccelerationData.Acceleration2D);
    AccelerationData.bIsAccelerating = AccelerationData.Acceleration > 0;
    AccelerationData.NormalizedAccel = AccelerationData.Acceleration2D;
    AccelerationData.NormalizedAccel.Normalize();
    AccelerationData.PivotDirection = UKismetMathLibrary::VLerp(AccelerationData.PivotDirection, AccelerationData.NormalizedAccel, .5f);
    AccelerationData.PivotDirection.Normalize();
    const float AccelerationAngle = UKismetAnimationLibrary::CalculateDirection(AccelerationData.PivotDirection, RotationData.OwnerRotation);
    //AccelerationData.AccelerationDirection = UACFCCFunctionLibrary::GetOppositeDirectionFromAngle(accelerationAngle);


}

void UHyAnimInstance::UpdateStateData(const float& DeltaSeconds)
{
    if (!CharacterMovementComp)
    {
        ERR_V("CharacterMovementComp is nullptr");
        return;
    }
    
    MovementData.bIsOnGround = CharacterMovementComp->IsMovingOnGround();
    MovementData.bWasCrouching = MovementData.bIsCrouching;
    MovementData.bIsCrouching = CharacterOwner->bIsCrouched;
    MovementData.bCrouchChanged = MovementData.bIsCrouching != MovementData.bWasCrouching;
    MovementData.bWalkStateChanged = MovementData.bWasWalking != MovementData.bIsWalking;
    MovementData.bWasWalking = MovementData.bIsWalking;
    //MovementData.bIsStrafing = CharacterMovementComp->IsCharacterStrafing();
    //MovementData.bIsWalking = CharacterMovementComp->GetTargetLocomotionState() == ELocomotionState::EWalk; // || MovementComp->GetCurrentLocomotionState() == ELocomotionState::EIdle;
    //MovementData.bIsSwimming = CharacterMovementComp->IsSwimming();
}

void UHyAnimInstance::UpdateJump(const float& DeltaSeconds)
{
    if (!CharacterMovementComp)
    {
        ERR_V("CharacterMovementComp is nullptr");
        return;
    }

    JumpData.bIsJumping = false;
    JumpData.bIsFalling = false;
    JumpData.bIsInAir = CharacterMovementComp->IsFalling();
    if (JumpData.bIsInAir) 
    {
        if (VelocityData.WorldSpeed.Z > 0.f) 
        {
            JumpData.bIsJumping = true;
        }
        else 
        {
            JumpData.bIsFalling = true;
        }
    }

    // TODO 여기서부터 진행!!
    JumpData.GroundDistance;

    //const FCharacterGroundInfo& GroundInfo = CharacterMovementComp->GetGroundInfo();
    //GroundDistance = GroundInfo.GroundDistance;

    //if (JumpData.bIsJumping) 
    //{
    //    JumpData.TimeToApex = UKismetMathLibrary::SafeDivide(-WorldSpeed.Z, MovementComp->GetGravityZ());
    //}
    //else {
    //    JumpData.TimeToApex = 0.f;
    //}
}
