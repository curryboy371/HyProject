// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "HyCoreTypes.h"

#include "Engine/DamageEvents.h"


#include "GameplayTagContainer.h"
#include "CollisionTypes.generated.h"

#pragma region Collision Channels

// Define Collision Channel
#define CPROFILE_HYCHARACTER TEXT("HyCharacterCapsule")
#define CPROFILE_HYATTACK TEXT("HyAttackCollider")

// HyAttackCollider - Character Capsule의 디테일한 Sweep 이벤트 감지를 위해 추가
// Pawn, HyCharacterCapsule에만 Overlapp
#define CCHANNEL_HYATTACK ECC_GameTraceChannel1

// HyAttackCollider에만 Overlapp - 캐릭터 주변 attack collider를 탐지하여 회피 액션을 취할 수 있도록 함
#define CCHANNEL_HYCHARACTER ECC_GameTraceChannel2

#pragma endregion


#pragma region Collision Enums

// Enumeration for Attack Collision Setting Types
UENUM(BlueprintType)
enum class EAttackCollisionSetting : uint8
{
    // Set new attack collision type, clears existing settings
    ACS_SetNew UMETA(DisplayName = "Set New Attack Collision Type"),

    // Clear hit objects and collider list, but keep existing collisions
    ACS_ClearHitList UMETA(DisplayName = "Clear Hit Objects and Collider List"),

    // Only perform sweep collisions at notification time
    ACS_SweepOnly UMETA(DisplayName = "Sweep Collision Only"),

    // Reset all attack collision types
    ACS_Reset UMETA(DisplayName = "Reset All Attack Collision Types"),
};

// Enumeration for Attack Collider Types
UENUM(BlueprintType)
enum class EAttackColliderType : uint8
{
    // Allow all colliders during attack state
    ACT_EnableAll UMETA(DisplayName = "Allow All Colliders"),

    // Only the first collider attack is allowed, subsequent ones are ignored
    ACT_EnableFirst UMETA(DisplayName = "Allow Only First Collider"),
};

// Enumeration for Damage Types
UENUM(BlueprintType)
enum class EHyDamageType : uint8
{
    EHyDamage_Normal UMETA(DisplayName = "Normal Damage"),
    EHyDamage_Large UMETA(DisplayName = "Normal Damage"),
    EHyDamage_Critical UMETA(DisplayName = "Critical Damage"),
    EHyDamage_Miss UMETA(DisplayName = "Miss Damage"),
};


UENUM(BlueprintType)
enum class ECombatDirection : uint8
{
    EForward UMETA(DisplayName = "Forward"),
    ERight UMETA(DisplayName = "Right"),
    ELeft UMETA(DisplayName = "Left"),
    EBack UMETA(DisplayName = "Back"),
    EForwardRight UMETA(DisplayName = "ForwardRight"),
    EForwardLeft UMETA(DisplayName = "ForwardLeft"),
    EBackRight UMETA(DisplayName = "BackRight"),
    EBackLeft UMETA(DisplayName = "BackLeft"),
    EDirectionMax UMETA(Hidden)
};


#pragma endregion


#pragma region Collision Structs

// Struct for Attack Collision Settings
USTRUCT(BlueprintType)
struct FAttackCollisionSettings : public FTagBase
{
    GENERATED_BODY()

public:
    FAttackCollisionSettings()
    {
        ResetState();
    }

    void ResetSettings()
    {
        AttackableUnitCount = 1;
        SettingType = EAttackCollisionSetting::ACS_SweepOnly;
        SpasticityTime = 0.0f;
        ColliderType = EAttackColliderType::ACT_EnableAll;
        bForceCameraShake = false;
        bForceSpasticity = false;
        bPlayHitEffect = false;
    }

    void ResetState()
    {
        AttackableUnitCount = 1;
        SettingType = EAttackCollisionSetting::ACS_SetNew;
        SpasticityTime = 0.0f;
        ColliderType = EAttackColliderType::ACT_EnableAll;
        bForceCameraShake = false;
        bForceSpasticity = false;
        bPlayHitEffect = true;
    }

    void ResetAll()
    {
        AttackableUnitCount = 1;
        SettingType = EAttackCollisionSetting::ACS_Reset;
        SpasticityTime = 0.0f;
        ColliderType = EAttackColliderType::ACT_EnableAll;
        bForceCameraShake = false;
        bForceSpasticity = false;
        bPlayHitEffect = false;
    }

    UPROPERTY(EditAnywhere, Category = "Collision Settings")
    EAttackCollisionSetting SettingType;

    UPROPERTY(EditAnywhere, Category = "Collision Settings")
    EAttackColliderType ColliderType;

    UPROPERTY(EditAnywhere, Category = "Collision Settings")
    TArray<FGameplayTag> AttackColliderTags;

    // 0: No Limit
    UPROPERTY(EditAnywhere, Category = "Collision Settings")
    int32 AttackableUnitCount;

    UPROPERTY(EditAnywhere, Category = "Effects")
    FCameraShakeSettings CameraShakeSettings;

    UPROPERTY(EditAnywhere, Category = "Effects")
    bool bForceCameraShake;

    UPROPERTY(EditAnywhere, Category = "Effects")
    bool bPlayHitEffect;

    UPROPERTY(EditAnywhere, Category = "Effects")
    bool bForceSpasticity;

    UPROPERTY(EditAnywhere, Category = "Effects")
    float SpasticityTime;
};

// Struct for Collider Trace Information
USTRUCT(BlueprintType)
struct FColliderTraceInfo : public FTagBase
{
    GENERATED_BODY()

public:
    FColliderTraceInfo()
    {
        Radius = 0.f;
        Height = 0.f;
		StartSocket = NAME_None;
		EndSocket = NAME_None;
		bCrossFrameAccuracy = false;
		bIsFirstFrame = true;
    }

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Settings")
    float Radius;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Settings")
    float Height;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Settings")
    FName StartSocket;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Settings")
    FName EndSocket;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Settings")
    bool bCrossFrameAccuracy;

    bool bIsFirstFrame;

    FVector PreEndSocketPos;
    FVector PreStartSocketPos;
};


USTRUCT(BlueprintType)
struct FTraceData
{
    GENERATED_BODY()

    FTraceData()
        : StartLocation(FVector::ZeroVector)
        , EndLocation(FVector::ZeroVector)
        , DiffTrace(FVector::ZeroVector)
        , DiffTraceRotation(FRotator::ZeroRotator)
        , TraceHeight(0.0f)
        , TraceRadius(0.0f)
    {

    }

    FTraceData(const FVector& InStart, const FVector& InEnd, const float& InTraceRadius, const float& InTraceHeight)
        :StartLocation(InStart)
    {
        TraceHeight = InTraceHeight;


        DiffTrace = InEnd - InStart;
        DiffTraceRotation = DiffTrace.GetSafeNormal().Rotation();
        TraceRadius = InTraceRadius;

        EndLocation = StartLocation + DiffTrace.GetSafeNormal2D() * TraceHeight;


    }

    void Reset()
    {
        StartLocation = EndLocation = FVector::ZeroVector;
        DiffTraceRotation = FRotator::ZeroRotator;
        TraceHeight = TraceRadius = 0.0f;
    }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector StartLocation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector EndLocation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector DiffTrace;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRotator DiffTraceRotation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float TraceHeight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float TraceRadius;
};






USTRUCT()
struct FHyDamageEvent : public FDamageEvent
{
    GENERATED_BODY()

    FHyDamageEvent()
        : HitTag(FGameplayTag::EmptyTag), DamageType(EHyDamageType::EHyDamage_Normal)
    {
        DealerGuid.Invalidate();
        ActionContext = "";
        AttackDirection = FVector::ZeroVector;
        DownTime = 0.0f;
    }


    virtual ~FHyDamageEvent() { }


    /** ID for this class. NOTE this must be unique for all damage events. */
    static const int32 ClassID = 3;

    virtual int32 GetTypeID() const override { return FHyDamageEvent::ClassID; };
    virtual bool IsOfType(int32 InID) const override { return (FHyDamageEvent::ClassID == InID) || FDamageEvent::IsOfType(InID); };

    void SetHitResult(const FHitResult& InHitResult) { HitResult = InHitResult; };
    const FHitResult& GetHitResult() const { return HitResult; };

    UPROPERTY()
    FGuid DealerGuid;

    UPROPERTY()
    FGameplayTag HitTag;

    UPROPERTY()
    FHitResult HitResult;

    UPROPERTY()
    EHyDamageType DamageType;

    UPROPERTY()
    FString ActionContext;

    UPROPERTY()
    FVector AttackDirection;

    UPROPERTY()
    float DownTime;

};

#pragma endregion


