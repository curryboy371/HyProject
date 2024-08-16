// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/HyAnimInstance.h"

#include "Animation/HyAnimEquipLayer.h"
#include "Animation/HyAnimLayer.h"

#include "HyCoreMacro.h"



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

UHyAnimInstance* UHyAnimInstance::GetOwningAnimInstance() const
{
    // TOOD
    // 레이어에서 프로퍼티 액세스 하려는 용도인데..
    // 레이어도 이 클래스를 상속하여 프로퍼티 액세스를 할지
    // 프로퍼티 액세스 없는 더 좋은 방법이 있는지 고민 필요 
    
    if (AActor* OwningActor = GetOwningActor())
    {
        ACharacter* OwningCharacter = Cast<ACharacter>(OwningActor);

        if (OwningCharacter)
        {
            if (UAnimInstance* AnimInstance = OwningCharacter->GetMesh()->GetAnimInstance())
            {
                UHyAnimInstance* OwningAnimInstance = Cast<UHyAnimInstance>(AnimInstance);
                if (OwningAnimInstance)
                {
                    return OwningAnimInstance;
                }
            }
        }
    }
    return nullptr;
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
