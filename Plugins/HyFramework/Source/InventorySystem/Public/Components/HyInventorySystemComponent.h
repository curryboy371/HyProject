// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HyInventorySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UHyInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




public:
	void AttachWeaponOnBody(TObjectPtr<class AHyWeapon> InWeaponToEquip);
	void AttachWeaponOnHand(TObjectPtr<class AHyWeapon> InWeaponToEquip);
		



protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inven")
	TObjectPtr<class USkeletalMeshComponent> CharacterOwnerMesh;
};
