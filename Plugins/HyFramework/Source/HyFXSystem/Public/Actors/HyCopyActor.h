// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HyCopyActor.generated.h"

UCLASS()
class HYFXSYSTEM_API AHyCopyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHyCopyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCopyActor(class USkeletalMeshComponent* InSkeletalMesh);

	UFUNCTION(BlueprintImplementableEvent)
	void SetDuration();

	TObjectPtr<class UPoseableMeshComponent> GetPosableMesh() { return PoseableMesh; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<class UMaterialInterface> PoseableMI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<class UMaterialInterface> CustomDepthMI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<class UPoseableMeshComponent> PoseableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FX)
	TObjectPtr<class UPoseableMeshComponent> CustomDepthMesh;
};
