// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HyWeapon.h"

#include "Components/SkeletalMeshComponent.h"

#include "Table/Item_TableEntity.h"


AHyWeapon::AHyWeapon()
{
    HandleComp = CreateDefaultSubobject<USceneComponent>(TEXT("HandleComp"));

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    if (SkeletalMesh)
    {
        SkeletalMesh->SetupAttachment(HandleComp);
        SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
        SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

}

void AHyWeapon::InitializeItem(const FItem_TableEntity* InItemTableInfo)
{
    Super::InitializeItem(InItemTableInfo);


}
