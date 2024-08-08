// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HyFXTypes.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class ESpawnFXLocation : uint8
{
	ESpawnOnActorLocation UMETA(DisplayName = "Attached to Actor"),
	ESpawnAttachedToSocketOrBone UMETA(DisplayName = "Attached to Socket / Bone"),
	ESpawnAtLocation UMETA(DisplayName = "Spawn On Provided Tranform")
};


// 이펙트 사운드를 하나로 처리하기 위한 Base 구조체
USTRUCT(BlueprintType)
struct FBaseFX : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBaseFX()
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
		PSParticle = nullptr;
	}

	FBaseFX(TObjectPtr<class USoundBase> InSound, TObjectPtr<class UNiagaraSystem> InNSParticle, TObjectPtr<class UParticleSystem> InPSParticle)
	{
		ActionSound = InSound;
		NiagaraParticle = InNSParticle;
		PSParticle = InPSParticle;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	TObjectPtr<class USoundBase> ActionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	TObjectPtr<class UNiagaraSystem> NiagaraParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	TObjectPtr<class UParticleSystem> PSParticle;
};





USTRUCT(BlueprintType)
struct FActionFX : public FBaseFX 
{
	GENERATED_BODY()

public:
	FActionFX()
		:SpawnLocation(ESpawnFXLocation::ESpawnOnActorLocation), Guid(0, 0, 0, 0)
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
	}

	FActionFX(const FBaseFX& InbaseFX, const ESpawnFXLocation InLocationType, const FName& InName)
		:Guid(0, 0, 0, 0)
	{
		ActionSound = InbaseFX.ActionSound;
		NiagaraParticle = InbaseFX.NiagaraParticle;
		SpawnLocation = InLocationType;
		SocketOrBoneName = InName;

	}

	FGuid GetGuid() const { return Guid; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	FName SocketOrBoneName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	ESpawnFXLocation SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	float NoiseEmitted = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | FX")
	FTransform RelativeOffset;

private:
	UPROPERTY()
	FGuid Guid;
};

USTRUCT(BlueprintType)
struct FDispatchFX : public FBaseFX 
{
	GENERATED_BODY()

public:
	FDispatchFX()
	{
		ActionSound = nullptr;
		NiagaraParticle = nullptr;
		SpawnLocation = FTransform();
	}

	FDispatchFX(const FBaseFX& InbaseFX, const FVector& Inlocation)
	{
		ActionSound = InbaseFX.ActionSound;
		NiagaraParticle = InbaseFX.NiagaraParticle;
		SpawnLocation = FTransform(Inlocation);
	}

	FDispatchFX(const FActionFX& InActionFX, const FTransform& location)
	{
		ActionSound = InActionFX.ActionSound;
		NiagaraParticle = InActionFX.NiagaraParticle;
		SpawnLocation = location;
	}

	FDispatchFX(const FDispatchFX& InDispatchFX)
	{
		ActionSound = InDispatchFX.ActionSound;
		NiagaraParticle = InDispatchFX.NiagaraParticle;
		SpawnLocation = InDispatchFX.SpawnLocation;
	}

	UPROPERTY(BlueprintReadWrite, Category = "Hy | FX")
	FTransform SpawnLocation;
};

USTRUCT(BlueprintType)
struct FAttachedComponents
{
	GENERATED_BODY()

public:
	FAttachedComponents()
	{
		NiagaraComp = nullptr;
		AudioComp = nullptr;
		CascadeComp = nullptr;
	}

	UPROPERTY()
	TObjectPtr<class UParticleSystemComponent> CascadeComp;

	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> NiagaraComp;

	UPROPERTY()
	TObjectPtr<class UAudioComponent> AudioComp;
};




//UCLASS()
//class HyFXSystem_API UFXTypes : public UObject
//{
//	GENERATED_BODY()
//	
//	
//	
//	
//};
