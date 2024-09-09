// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyFXSystemComponent.h"

#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "HyCoreMacro.h"

UHyFXSystemComponent::UHyFXSystemComponent()
{
}

void UHyFXSystemComponent::InitializeHyActorComponent()
{
	Super::InitializeHyActorComponent();

}

void UHyFXSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHyFXSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHyFXSystemComponent::PlayAttachedFX(const FActionFX& InActionFX, ACharacter* InInstigator)
{
    if (InInstigator)
    {
        switch (InActionFX.SpawnLocation)
        {
        case ESpawnFXLocation::ESpawnOnActorLocation:
        case ESpawnFXLocation::ESpawnAttachedToSocketOrBone:
            SpawnAttachedFX(InActionFX, InInstigator);
            break;
        case ESpawnFXLocation::ESpawnAtLocation:
            //SpawnFXAtLocation(FDispatchFX(effect, effect.RelativeOffset), instigator);
            break;
        default:
            break;
        }
    }
    else
    {
        ERR_V("InInstigator is null");
    }
}

void UHyFXSystemComponent::StopFXAttached(const FActionFX& InActionFX, ACharacter* InInstigator)
{


}

void UHyFXSystemComponent::SpawnAttachedFX(const FActionFX& InActionFX, ACharacter* InInstigator)
{
    FAttachedComponents comps;
    if (InInstigator)
    {
        InActionFX.GetGuid().NewGuid();

        if (InInstigator->GetMesh()->DoesSocketExist(InActionFX.SocketOrBoneName))
        {
            if (InActionFX.ActionSound)
            {
                comps.AudioComp = UGameplayStatics::SpawnSoundAttached(InActionFX.ActionSound, InInstigator->GetMesh(), InActionFX.SocketOrBoneName);
            }

            if (InActionFX.NiagaraParticle)
            {
                comps.NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(InActionFX.NiagaraParticle, InInstigator->GetMesh(), InActionFX.SocketOrBoneName,
                    InActionFX.RelativeOffset.GetLocation(), InActionFX.RelativeOffset.GetRotation().Rotator(), InActionFX.RelativeOffset.GetScale3D(),
                    EAttachLocation::SnapToTarget, true, ENCPoolMethod::AutoRelease);
            }

            if (InActionFX.PSParticle)
            {
                comps.CascadeComp = UGameplayStatics::SpawnEmitterAttached(InActionFX.PSParticle, InInstigator->GetMesh(), InActionFX.SocketOrBoneName,
                    InActionFX.RelativeOffset.GetLocation(), InActionFX.RelativeOffset.GetRotation().Rotator(), InActionFX.RelativeOffset.GetScale3D());
            }

        }
        else
        {
            ERR_V("invalid socket name %s ", *InActionFX.SocketOrBoneName.ToString());
        }
    }
    else
    {
        ERR_V("InInstigator is null");
    }
}
