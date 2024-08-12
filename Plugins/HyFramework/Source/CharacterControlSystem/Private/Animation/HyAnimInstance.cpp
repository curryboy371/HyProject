// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"

#include "Animation/HyAnimEquipLayer.h"
#include "Animation/HyAnimLayer.h"

#include "HyCoreLogging.h"



#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
//#include "KismetAnimationLibrary.h"
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


}

void UHyAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();


}

void UHyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    // Animation Tread는 별도로 동작하니 Animinstace의 변수 업데이트는 threadsafe하게 update

    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

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

void UHyAnimInstance::SetEquipLayer(const FGameplayTag& InEquipTag)
{
    if (FHyAnimEquipLayerSet* FindEquipLayer = EquipLayers.FindByKey(InEquipTag))
    {
        if (FindEquipLayer->EquipLayer)
        {
            //if (CurEquipLayerInst)
            //{
            //    // TODO 필요시 종료 sign
            //}

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

}

void UHyAnimInstance::UpdateRotation(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateVelocity(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateAimData(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateAcceleration(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateStateData(const float& DeltaSeconds)
{

}

void UHyAnimInstance::UpdateJump(const float& DeltaSeconds)
{

}
