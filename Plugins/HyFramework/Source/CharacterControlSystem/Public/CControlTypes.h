// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyCoreTypes.h"
#include "InputTriggers.h"

#include "UObject/NoExportTypes.h"
#include "CControlTypes.generated.h"

/**
 * 
 */



#pragma region CControlEnum

UENUM(BlueprintType)
enum class ECharacterMovementMode : uint8
{
    EWalk UMETA(DisplayName = "Walk"),
    ERun UMETA(DisplayName = "Run"),
    EDash UMETA(DisplayName = "Dash"),
};

UENUM(BlueprintType)
enum class ECombatMode : uint8
{
    EPeace UMETA(DisplayName = "Peace Mode"),
    ECombat UMETA(DisplayName = "Combat Mode")
};

UENUM(BlueprintType)
enum class EKeyInput : uint8
{
    IA_None = 0,
	IA_Attack,
    IA_Equip,
	IA_Skill1,
	IA_Jump,
	IA_Move,
	IA_Look,
};

#pragma endregion


#pragma region CControlStruct
// Character State Struct 
USTRUCT(BlueprintType)
struct FCharacterStateData
{
    GENERATED_BODY()

    FCharacterStateData()
        : bIsDead(false)
        , CombatMode(ECombatMode::EPeace)
    {

    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Character")
    bool bIsDead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Character")
    ECombatMode CombatMode;
};


// Movement Structs
USTRUCT(BlueprintType)
struct FCharacterMovementData
{
    GENERATED_BODY()

    FCharacterMovementData()
        : MaxWalkSpeed(600.0f)               // 언리얼 기본 보행 속도
        , MaxAcceleration(2048.0f)           // 언리얼 기본 가속도
        , BrakingDeceleration(2048.0f)       // 언리얼 기본 걷기 감속도
        , BrakingFrictionFactor(2.0f)        // 언리얼 기본 브레이크 마찰 계수
        , BrakingFriction(0.0f)              // 언리얼 기본 브레이크 마찰력
        , UseSeparateBrakingFriction(false)  // 기본적으로 별도의 브레이크 마찰력 사용 안 함
    {
    }


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    float MaxWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    float MaxAcceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    float BrakingDeceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    float BrakingFrictionFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    float BrakingFriction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    bool UseSeparateBrakingFriction;

};





// Layer Structs

USTRUCT(BlueprintType)
struct FHyAnimEquipLayerSet : public FTagBase
{
    GENERATED_BODY()

public:
    FHyAnimEquipLayerSet() {}

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Layer")
    TSubclassOf<class UHyAnimEquipLayer> EquipLayer;
};

// Input Structs

USTRUCT(BlueprintType)
struct FCharacterInputData
{
    GENERATED_BODY()
      
    FCharacterInputData()
		: InputDirection(FVector::ZeroVector)
        , LastInputDirection(FVector::ZeroVector)
		, InputRotator(FRotator::ZeroRotator)
		, DashDirection(FVector::ZeroVector)
	{
        bIsMoveInputing = false;
        InputScale = 0.f;
        RotationSpeed = 20.f;
        RotationToleranceAngle = 90.f;
	}
    void SetInputDirection2D(const FVector& InInputDirection)
	{
        InputDirection = InInputDirection.GetSafeNormal2D();
        InputDirection.Z = 0.f;
	}

    void SetInputRotator2D(const FRotator& InInputRotator)
	{
		InputRotator = InInputRotator;
		InputRotator.Pitch = 0.0f;
		InputRotator.Roll = 0.0f;
	}

    void SetLastInputDirection()
    {
        LastInputDirection = InputDirection;
    }

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    FVector InputDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    FVector LastInputDirection;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    FRotator InputRotator;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Movement")
    FVector DashDirection;

    // 회전 속도
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CControl | Movement")
    float RotationSpeed;

    // 회전 오차범위 ( 회전이 완료되면 이동 시작 )
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "CControl | Movement")
    float RotationToleranceAngle;

    // Move Input Length
    float InputScale;

    // Move Input 입력중인지
    bool bIsMoveInputing;
};


// Input Mapping Datas
USTRUCT(BlueprintType)
struct FInputActionData
{
    GENERATED_BODY()

public:
    FInputActionData()
        : 
          InputKey(EKeyInput::IA_None)
        , InputAction(nullptr)
        , TriggerEvent(ETriggerEvent::Triggered)
        , ActionMethodName(NAME_None)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    EKeyInput InputKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    class UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    ETriggerEvent TriggerEvent;

    // Method name to call
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Action")
    FName ActionMethodName;  
};

USTRUCT(BlueprintType)
struct FInputDataSet : public FTagBase
{
    GENERATED_BODY()

public:
    FInputDataSet() 
    {
        InputContext = nullptr;
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Input")
    class UInputMappingContext* InputContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CControl | Input")
    TArray<FInputActionData> InputDatas;
};


USTRUCT(BlueprintType)
struct FCControlUpdates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateMovementData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateLocationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateRotationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateSpeedData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateAccelerationData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateAimData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateJumpData = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Updates")
    bool bUpdateLeaningData = true;
};


#pragma endregion
