// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HyItem.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "HyCoreMacro.h"


// Sets default values
AHyItem::AHyItem()
{
	// 생성시 디폴트 숨김
	SetActorHiddenInGame(false);


	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	if (ItemMesh)
	{
		ItemMesh->SetupAttachment(RootComp);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHyItem::InitializeItem(const FItem_TableEntity* InItemTableInfo)
{
	if (InItemTableInfo)
	{
		ItemTableInfo = *InItemTableInfo;
	}
	else
	{
		ERR_V("InItemTableInfo is nullptr");
	}
}

