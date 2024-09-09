// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/HyCopyActor.h"

#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SkinnedMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"


#include "HyCoreMacro.h"


// Sets default values
AHyCopyActor::AHyCopyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComp"));
	SetRootComponent(PoseableMesh);
	PoseableMesh->SetCastShadow(false);

	CustomDepthMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("CustomDepthMeshComp"));
	CustomDepthMesh->SetupAttachment(PoseableMesh);
	CustomDepthMesh->bRenderInMainPass = 0;
	CustomDepthMesh->bRenderInDepthPass = 0;
	CustomDepthMesh->bRenderCustomDepth = 1;
	CustomDepthMesh->SetCastShadow(false);
}

// Called when the game starts or when spawned
void AHyCopyActor::BeginPlay()
{
	Super::BeginPlay();






}

// Called every frame
void AHyCopyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHyCopyActor::SetCopyActor(USkeletalMeshComponent* InSkeletalMesh)
{
	if (!PoseableMI)
	{
		ERR_V("PoseableMI is nullptr");
		return;
	}

	if (!CustomDepthMI)
	{
		ERR_V("CustomDepthMI is nullptr");
		return;
	
	}

	if (!InSkeletalMesh)
	{
		ERR_V("InSkeletalMesh is nullptr");
		return;
	}

	if (!PoseableMesh)
	{
		ERR_V("PoseableMesh is nullptr");
		return;
	}

	if (!CustomDepthMesh)
	{
		ERR_V("CustomDepthMesh is nullptr");
		return;
	}

	CustomDepthMesh->SetRenderInMainPass(false);
	CustomDepthMesh->SetRenderInDepthPass(false);
	CustomDepthMesh->SetRenderCustomDepth(true);
	PoseableMesh->SetCastShadow(false);

	if (USkinnedAsset* SkinnedAsset = InSkeletalMesh->GetSkinnedAsset())
	{
		PoseableMesh->SetSkinnedAssetAndUpdate(SkinnedAsset);
		PoseableMesh->CopyPoseFromSkeletalComponent(InSkeletalMesh);

		int32 MaterialNum = PoseableMesh->GetMaterials().Num();

		for(int32 i = 0; i < MaterialNum; ++i)
		{
			PoseableMesh->SetMaterial(i, PoseableMI);
		}

		CustomDepthMesh->SetSkinnedAssetAndUpdate(SkinnedAsset);
		CustomDepthMesh->CopyPoseFromSkeletalComponent(InSkeletalMesh);

		MaterialNum = CustomDepthMesh->GetMaterials().Num();

		for (int32 i = 0; i < MaterialNum; ++i)
		{
			CustomDepthMesh->SetMaterial(i, CustomDepthMI);
		}
	}

	SetDuration();
}

