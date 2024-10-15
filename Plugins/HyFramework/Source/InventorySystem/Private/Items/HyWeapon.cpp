// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HyWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "NiagaraComponent.h"


#include "NiagaraFunctionLibrary.h"

#include "Table/Item_TableEntity.h"

#include "GameplayTagContainer.h"

#include "HyCoreMacro.h"

AHyWeapon::AHyWeapon()
{
    SubHandleComp = CreateDefaultSubobject<USceneComponent>(TEXT("SubHandleComp"));

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    if (SkeletalMesh)
    {
        SkeletalMesh->SetupAttachment(RootComp);
        SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
        SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    }

    SubWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubWeaponMesh"));
    if (SubWeaponMesh)
    {
        SubWeaponMesh->SetupAttachment(SubHandleComp);
        SubWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

}

void AHyWeapon::InitializeItem(const FItem_TableEntity* InItemTableInfo)
{
    Super::InitializeItem(InItemTableInfo);


}

void AHyWeapon::ActiveTrail(bool bActive, const EHyAttackTrailType InAttackTrailType)
{
    if (bActive)
    {
        if (TObjectPtr<UNiagaraSystem>* NiagaraParticle = NiagaraTrailMap.Find(InAttackTrailType))
        {
            if (TObjectPtr<UNiagaraComponent>* TrailComp = NiagaraCompMap.Find(InAttackTrailType))
            {
				if (*TrailComp && !(*TrailComp)->IsActive())
				{
                    NiagaraCompMap.Remove(InAttackTrailType);
				}
            }

            TObjectPtr<UNiagaraComponent> NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
                *NiagaraParticle,
                SkeletalMesh,  // 파티클이 붙을 컴포넌트
                ItemTableInfo.EndSocketName,           // 소켓 이름
                FVector::ZeroVector, // 위치
                FRotator::ZeroRotator, // 회전
                EAttachLocation::KeepRelativeOffset, // 상대 위치 유지
                false               // 데토네이션 시 시스템 제거 여부
            );

            NiagaraCompMap.Add(InAttackTrailType, NiagaraComponent);
        }
    }
    else
    {
        if (TObjectPtr<UNiagaraComponent>* TrailComp = NiagaraCompMap.Find(InAttackTrailType))
        {
            if (*TrailComp)
            {
                (*TrailComp)->Deactivate();
            }

            NiagaraCompMap.Remove(InAttackTrailType);
        }
    }

}

TObjectPtr<UNiagaraComponent> AHyWeapon::ActiveWeaponTrail(const EHyAttackTrailType InAttackTrailType)
{
    if (TObjectPtr<UNiagaraSystem>* NiagaraParticle = NiagaraTrailMap.Find(InAttackTrailType))
    {
        TObjectPtr<UNiagaraComponent> NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
            *NiagaraParticle,
            SkeletalMesh,  // 파티클이 붙을 컴포넌트
            ItemTableInfo.EndSocketName,           // 소켓 이름
            FVector::ZeroVector, // 위치
            FRotator::ZeroRotator, // 회전
            EAttachLocation::KeepRelativeOffset, // 상대 위치 유지
            false               // 데토네이션 시 시스템 제거 여부
        );

        return NiagaraComponent;
    }
    else
    {
		ERR_V("Invalid NiagaraTrailMap Key %d", (int32)InAttackTrailType);
	}

    return nullptr;
}
