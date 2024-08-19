// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HyItem.generated.h"

UCLASS()
class INVENTORYSYSTEM_API AHyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;





public:
	FORCEINLINE void SetItemOwner(TObjectPtr<class APawn> InOwner) { ItemOwner = InOwner;}


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inven")
	TObjectPtr<class APawn> ItemOwner;
};
