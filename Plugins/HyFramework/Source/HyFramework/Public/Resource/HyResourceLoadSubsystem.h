// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Engine/AssetManager.h"


#include "HyCoreMacro.h"

#include "HyResourceLoadSubsystem.generated.h"

/**
 *   Object 비동기 로딩을 위한 서브시스템
 */

// 생성할 Object의 Type
UENUM(BlueprintType)
enum class EGenerateType : uint8
{
	EGen_None UMETA(DisplayName = "EGen_None"),
	EGen_Character UMETA(DisplayName = "EGen_Character"),
};

// Object 생성시 사용할 C++ param
struct FResourceloaderArgument
{
public:
	bool bIsError = false;
	int32 ObjectID = 0;
	EGenerateType GenType = EGenerateType::EGen_None;
	FVector Location;
	FRotator Rotation;

private:
	UObject* ObjectPtr; // GenerateeObjectPtr

public:
	FResourceloaderArgument()
	{
		ObjectID = 0;
		GenType = EGenerateType::EGen_None;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}
	FResourceloaderArgument(uint32 InID, EGenerateType InGenType, FVector InLocation, FRotator InRotation)
	{
		ObjectID = InID;
		GenType = InGenType;
		Location = InLocation;
		Rotation = InRotation;
	}
	
	~FResourceloaderArgument();

	UObject* GetObjectPtr() { return ObjectPtr;	};
	void SetObjectPtr(UObject* InObject);
};

// Callback Deletage
DECLARE_DELEGATE_OneParam(FResourceLoaderAsyncDelegate, FResourceloaderArgument*);
DECLARE_DELEGATE_OneParam(FResourceLoaderProgressCountDelegate, int32);

UCLASS()
class HYFRAMEWORK_API UHyResourceLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void LoadMemoryAsync(const FName& InPath, FResourceloaderArgument* InArg, FResourceLoaderAsyncDelegate DelegateToCall);

protected:



protected:
	const bool CheckVaildPath(const FName& InPath) const;
	const bool FileExists(const FName& InPath) const;

};
