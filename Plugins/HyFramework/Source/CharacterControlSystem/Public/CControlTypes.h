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
#pragma region CControlDefine

// 캐릭터가 이동중인지 확인하는 임계값
#define MOVEMENT_SPEED_THRESHOLD 0.2f



#pragma endregion


#pragma region CControlEnum

UENUM(BlueprintType)
enum class ECharacterMovementMode : uint8
{
    EWalk UMETA(DisplayName = "Walk"),
    ERun UMETA(DisplayName = "Run"),
    EDash UMETA(DisplayName = "Dash"),
};

UENUM(BlueprintType)
enum class ELocomotionState : uint8 
{
    EIdle = 0 UMETA(DisplayName = "Idle"),
    EWalk = 1 UMETA(DisplayName = "Walk"),
    EJog = 2 UMETA(DisplayName = "Jog"),
    ESprint = 3 UMETA(DisplayName = "Sprint"),
};

UENUM(BlueprintType)
enum class EMovementStance : uint8 
{
    EIdle = 0 UMETA(DisplayName = "Idle"),
    EAiming = 1 UMETA(DisplayName = "Aiming"),
    EBlock = 2 UMETA(DisplayName = "Blocking"),
    ECustom = 3 UMETA(DisplayName = "Custom"),
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
	IA_RAttack,
	IA_ChargeAttack,
    IA_Equip,
	IA_Skill1,
	IA_Skill2,
	IA_Skill3,
	IA_Skill4,
	IA_Skill5,
    IA_Ulti,

	IA_Jump,
	IA_Move,
	IA_Look,

    IA_Crouch,
    IA_Sprint,
    IA_Dodge,


    IA_CameraZoom,

};

#pragma endregion


#pragma region CControlStruct

// Character Animation Struct

USTRUCT(BlueprintType)
struct FAnimationJumpData
{
    GENERATED_BODY()

public:
    FAnimationJumpData()
        : bIsInAir(false)
		, bIsJumping(false)
		, bIsFalling(false)
        , GroundDistance(-1.0f)
	{
	}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Animation | Jump")
    bool bIsInAir;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Animation | Jump")
    bool bIsJumping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Animation | Jump")
    bool bIsFalling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Animation | Jump")
    float GroundDistance;
};

USTRUCT(BlueprintType)
struct FAnimationMovementData
{
    GENERATED_BODY()

public:
    FAnimationMovementData()
		:
          CurLocomotionState(ELocomotionState::EIdle)
        , bIsCrouching(false)
		, bWasCrouching(false)
		, bCrouchChanged(false)
		, bIsOnGround(false)
        , bIsWalking(false)
        , bWasWalking(false)
        , bWalkStateChanged(false)
        , bIsStrafing(false)
        , bIsSwimming(false)
        
	{
    }

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    ELocomotionState CurLocomotionState;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bIsCrouching;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bWasCrouching;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bCrouchChanged;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bIsOnGround;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bIsWalking;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bWasWalking;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bWalkStateChanged;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bIsStrafing;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    bool bIsSwimming;
};

USTRUCT(BlueprintType)
struct FAnimationLocationData
{
    GENERATED_BODY()

public:
    FAnimationLocationData()
    {
        Displacement = 0.f;
		DisplacementDelta = 0.f;
		OwnerLocation = FVector::ZeroVector;
    }

    UPROPERTY(BlueprintReadOnly, Category = "Location")
    float Displacement;

    UPROPERTY(BlueprintReadOnly, Category = "Location")
    float DisplacementDelta;

    UPROPERTY(BlueprintReadOnly, Category = "Location")
    FVector OwnerLocation;

};

USTRUCT(BlueprintType)
struct FAnimationAccelerationData
{
    GENERATED_BODY()

public:
    FAnimationAccelerationData()
    {
        bIsAccelerating = false;
		Acceleration = 0.f;
        AccelerationRatio = 0.0f;
		Acceleration2D = FVector::ZeroVector;
		NormalizedAccel = FVector::ZeroVector;
		LocalAccel2D = FVector::ZeroVector;
		PivotDirection = FVector::ZeroVector;
		TimeSinceLastPivot = 0.f;
        AccelerationDirection = EHyDirection::Front;
    }

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    bool bIsAccelerating;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    float Acceleration;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    float AccelerationRatio;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    FVector Acceleration2D;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    FVector NormalizedAccel;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    FVector LocalAccel2D;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    EHyDirection AccelerationDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Acceleration")
    FVector PivotDirection;

    UPROPERTY(BlueprintReadWrite, Category = "Acceleration")
    float TimeSinceLastPivot;
};

USTRUCT(BlueprintType)
struct FAnimationVelocityData
{
    GENERATED_BODY()

public:
    FAnimationVelocityData()
    {
        bWasMoving = false;
        bIsMoving = false;
        bIsMaxSpeed = false;

        Direction = 0.f;
        DirectionWithOffset = 0.f;
        Speed = 0.f;
        DeltaInputDirection = 0.f;
        NormalizedSpeed = 0.f;
        PreviousSpeed = 0.f;
        NormalizedSwimSpeed = 0.f;
        WorldSpeed = FVector::ZeroVector;
        WorldSpeed2D = FVector::ZeroVector;
        LocalSpeed2D = FVector::ZeroVector;

        SpeedDirection = EHyDirection::Front;
        SpeedDirectionWithOffset = EHyDirection::Front;
        LastSpeedDirection = EHyDirection::Front;
        LastSpeedDirectionWithOffset = EHyDirection::Front;
    }

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    bool bWasMoving;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    bool bIsMoving;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float Direction;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float DirectionWithOffset;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float Speed;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float DeltaInputDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float NormalizedSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float PreviousSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    float NormalizedSwimSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    FVector WorldSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    FVector WorldSpeed2D;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    FVector LocalSpeed2D;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    EHyDirection SpeedDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    EHyDirection SpeedDirectionWithOffset;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    EHyDirection LastSpeedDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    EHyDirection LastSpeedDirectionWithOffset;

    UPROPERTY(BlueprintReadOnly, Category = "Velocity")
    bool bIsMaxSpeed;
};



USTRUCT(BlueprintType)
struct FAnimationRotationData
{
    GENERATED_BODY()

public:
    FAnimationRotationData()
    {
		OwnerRotation = FRotator::ZeroRotator;
		PreviousRotation = FRotator::ZeroRotator;
		YawSpeed = 0.f;
		YawDelta = 0.f;
		YawOffset = 0.f;
    }

    UPROPERTY(BlueprintReadOnly, Category = "Rotation")
    FRotator OwnerRotation;

    UPROPERTY(BlueprintReadOnly, Category = "Rotation")
    FRotator PreviousRotation;

    UPROPERTY(BlueprintReadOnly, Category = "Rotation")
    float YawSpeed = 0.f;

    UPROPERTY(BlueprintReadOnly, Category = "Rotation")
    float YawDelta = 0.f;

    UPROPERTY(BlueprintReadOnly, Category = "Rotation")
    float YawOffset = 0.f;
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

USTRUCT(BlueprintType)
struct FLocomotionState 
{
    GENERATED_BODY()

    FLocomotionState()
    {
        State = ELocomotionState::EWalk;
    };
    FLocomotionState(ELocomotionState InState, const FCharacterMovementData& InCharacterMovementData)
    {
        State = InState;
        CharacterMovementData = InCharacterMovementData;
    };

    FORCEINLINE const float GetMaxSpeed() const
    {
        return CharacterMovementData.MaxWalkSpeed;
    }

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    ELocomotionState State;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    FCharacterMovementData CharacterMovementData;

    // Struct Array에서 Key값을 사용하기 위하여 operator 선언
    FORCEINLINE bool operator==(const FLocomotionState& Other) const
    {
        return this->State == Other.State;
    }

    FORCEINLINE bool operator==(const ELocomotionState& Other) const
    {
        return this->State == Other;
    }

    FORCEINLINE bool operator!=(const FLocomotionState& Other) const
    {
        return this->State != Other.State;
    }

    FORCEINLINE bool operator!=(const ELocomotionState& Other) const
    {
        return this->State != Other;
    }
};

USTRUCT(BlueprintType)
struct FMovStances 
{
    GENERATED_BODY()

    FMovStances()
    {
        MovementStance = EMovementStance::EIdle;
        LocomotionState = ELocomotionState::EWalk;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
    EMovementStance MovementStance;

    FORCEINLINE bool operator!=(const EMovementStance& Other) const
    {
        return MovementStance != Other;
    }

    FORCEINLINE bool operator==(const EMovementStance& Other) const
    {
        return MovementStance == Other;
    }

    FORCEINLINE bool operator!=(const FMovStances& Other) const
    {
        return MovementStance != Other.MovementStance;
    }

    FORCEINLINE bool operator==(const FMovStances& Other) const
    {
        return MovementStance == Other.MovementStance;
    }

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
    ELocomotionState LocomotionState;
};




// Character State Struct 
USTRUCT(BlueprintType)
struct FCharacterStateData : public FTagBase
{
    GENERATED_BODY()

    FCharacterStateData()
        : bIsDead(false)
        , CombatMode(ECombatMode::EPeace)
    {
    }

    void SetCombatMode(const bool bCombatMode)
	{
		CombatMode = bCombatMode ? ECombatMode::ECombat : ECombatMode::EPeace;
	}

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Character")
    bool bIsDead;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CControl | Character")
    ECombatMode CombatMode;
};

// 캐릭터 디폴트 태그
USTRUCT(BlueprintType)
struct FCharacterDefaultTagSet
{
    GENERATED_BODY()

public:
    FCharacterDefaultTagSet()
    {
        InputTag = FGameplayTag::EmptyTag;
        CombatEquipTag = FGameplayTag::EmptyTag;
        PeaceEquipTag = FGameplayTag::EmptyTag;
        ActionTag = FGameplayTag::EmptyTag;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | ControlTag")
    FGameplayTag InputTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | ControlTag")
    FGameplayTag CombatEquipTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | ControlTag")
    FGameplayTag PeaceEquipTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | ControlTag")
    FGameplayTag ActionTag;
};





// Character DebugData Set
USTRUCT(BlueprintType)
struct FCharacterDebugData
{
    GENERATED_BODY()
    FCharacterDebugData()
    {
        DebugWidgetLocation = FVector::ZeroVector;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CControl | Debug")
    FVector DebugWidgetLocation;
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
