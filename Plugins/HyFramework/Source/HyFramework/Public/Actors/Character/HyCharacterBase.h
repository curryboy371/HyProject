// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "GameFramework/DamageType.h"

#include "HyCoreTypes.h"
#include "HyTypes.h"

#include "CControlTypes.h"

#include "ActionsTypes.h"


#include "InputActionValue.h"

#include "Interface/HyCharacterCombatInterface.h"
#include "Interface/CControlCharacterInterface.h"
#include "Interface/ActionsCharacterInterface.h"
#include "Interface/CollisionCharacterInterface.h"


#include "HyCharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipTagChanged, const FGameplayTag&, EquipTag, const bool, bIsCombatMode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageReceived, const FHyDamageEvent&, DamageReceived, const FGuid&, InDealerGuid);



UCLASS()
class HYFRAMEWORK_API AHyCharacterBase : public ACharacter
										, public ICControlCharacterInterface
										, public IActionsCharacterInterface	
										, public ICollisionCharacterInterface
										, public IHyCharacterCombatInterface

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyCharacterBase(const FObjectInitializer& ObjectInitializer);


public:
	void SpawnCompleted(const int32 InSpawnID = 0);
	void SetGroundLocation();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void CharacterDefaultSetup();
	virtual void ComponenetSetup();

protected:
	void CharacterAIDefaultSetup();

	void CharacterActionTagSetup();

	void CharacterSetup();
	void CharacterActorComponentSetup();
	void CharacterCombatArrowSetup();

	void SetDelegateFunctions();
	void CharacterWidgetSetup();
	void CharacterDebugHudSetup();


	void MatchArrowComponenLocation();

public:
	// Guid
	const FGuid& GetMyGuid() const { return MyGuid; }
	FGuid& GetMyGuidRef() { return MyGuid; }

	const FGuid& GetTargetGuid() const { return TargetGuid; }
	FGuid& GetTargetGuidRef() { return TargetGuid; }

	const bool IsTargetAvailable();

	const FGameplayTag& GetCharacterTypeTag() const { return CharacterTypeTag; }

	const int32 GetSpawnID() const { return SpawnID; }

public:
	// ICControlCharacterInterface을(를) 통해 상속됨
	virtual const bool IsDead() override;
	virtual const bool IsCombatMode() const override;

	virtual FGameplayTag GetEquipTag() override;

	virtual void SetCombatMode(const bool bCombatMode) override;


	const bool IsCrouching() const;

	// about Inventory...
	const bool IsWeaponOnHand();


public:
	// Test
	UFUNCTION(BlueprintCallable)
	virtual bool TriggerActionBlueprint(FActionExcuteData InActionExcuteData, const FString& InContext = "", bool bCanBeStored = false);

	// IActionsCharacterInterface을(를) 통해 상속됨
	virtual bool TriggerAction(FGameplayTag& InActionTag, EActionPriority InPriority, const FString& InContext = "", bool bCanBeStored = false) override;
	virtual bool TriggerAction(FActionExcuteData& InActionExcuteData, const FString& InContext = "", bool bCanBeStored = false) override;
	virtual void SetStoredAction(FActionExcuteData& InActionExcuteData, const FString InContext = "", bool bForce = false) override;
	virtual void SetStoredAction(FGameplayTag& InActionTag, EActionPriority InPriority, const FString& InContext = "", bool bForce = false) override;
	virtual void HandleAction(EActionHandleType InExitType, float BlendOut = 0.5f) override;

	virtual void SetPerformingActionPriority(EActionPriority InPriority = EActionPriority::EEmpty) override;

	virtual bool CompareCurrentPriority(EActionPriority InPriority) const override;


	virtual const bool IsEmptyStoredAction() const override;
	virtual const bool IsCanStoreAction(EActionPriority InPriority) const override;

	virtual const FGameplayTag GetCurAction() const override;
	virtual const FGameplayTag GetStoredAction() const override;

public:
	// IHyCharacterCombatInterface을(를) 통해 상속됨
	virtual const bool IsTargetInRange(const float InRange) override;
	virtual const bool SetCharacterRotationIfInRange(const FVector& InTargetLotation, const float InEnableRange) override;

	// TODO 나중에 인터페이스로 옮기자
	const bool FindNearAttackCollider(const float InExtendRatio);
	void SetAirHitWarpLocation(const FVector& InLocation);
	const FVector& GetAirHitWarpLocation() const { return CharacterCombatDataSet.AirHitLocation; }

	// Combat

	bool GetNextCombatArrowCommand(ECombatDirection& OutArrowDirection);
	void SetCombatArrowCommandQueue();

	bool GetCombatArrowLocation(const ECombatDirection InDirection, FVector& OutCombatArrowLocation);
	bool GetClosestCombatArrow(const FVector& InAttackerLocation, const float InOwnerAttackRange, FVector& OutCombatArrowLocation);
	void SetWarpingTarget(const FVector& InTargetLocation, const FName& InWarpName);
	void ReleaseWarpingTarget(const FName& InWarpName);

	FVector GetLastAttackDirection() { return LastAttackDirection; }
public:

	// Anim 
	void SwitchEquipLayer(const FGameplayTag& InEquipTag);

	void SetHyAnimInstance();

	void SetStencilOutline(bool IsShow, EStencilOutLine StencilType );

public:
	

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputChargeAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputAirStartAttack(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CompletedMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputLook(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputEquip(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CompletedSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputDodge(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputCrouch(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSkill1(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSkill2(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSkill3(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSkill4(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputSkill5(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void InputUlti(const FInputActionValue& Value);
	
protected:
	void TriggerAttackAction();


protected:
	// ICollisionCharacterInterface을(를) 통해 상속됨
	virtual void EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet) override;
	virtual void NotifyAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet) override;
	virtual void DisableAttackCollider() override;


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void SetCharacterCollisionEnable(bool bEnable);


public:
	const bool IsDead() const;

	const bool IsCanAction(EKeyInput InKeyAction) const;

protected:
	// Debug
	void DebugUpdate();

	void DebugRenderWidget();
	void DebugDrawMovement();

	void DebugDrawTargetHitDirection();
public:


	TObjectPtr<class UHyInventorySystemComponent> GetInventorySystemComp() { return InventorySystemComp; }
	TObjectPtr<class UActionsSystemComponent> GetActionsSystemComp() { return ActionsSystemComp; }
	TObjectPtr<class UHyFXSystemComponent> GetFXSystemComp() { return FXSystemComponent; }
	TObjectPtr<class UHyCollisionSystemComponent> GetCollisionSystemComp() { return CollisionSystemComp; }
	TObjectPtr<class UHyCharacterMovementComponent> GetCharacterMovementComp() { return HyCharacterMovement; }

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TArray<TObjectPtr<class UHyActorComponent>> HyActorComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UActionsSystemComponent> ActionsSystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UHyInventorySystemComponent> InventorySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UHyCollisionSystemComponent> CollisionSystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UHyFXSystemComponent> FXSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class USceneComponent> CombatArrowParentComp;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Component")
	TObjectPtr<class USceneComponent> HUDLocationComp;

	UPROPERTY()
	TObjectPtr<class UHyCharacterMovementComponent> HyCharacterMovement;

protected:
	class TSharedPtr<class SHyCharacterHudDebugWidget> SCharacterDebugWidget;

	TMap<ECombatDirection, TObjectPtr<class UArrowComponent>> CombatArrowComponentMap;

public:
	UPROPERTY(BlueprintAssignable, Category = "Hy | Anim | Layer")
	FOnEquipTagChanged OnEquipTagChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hy | Combat")
	FOnDamageReceived OnDamageReceived;

public:
	static FQuickActionExcuteDataSet QuickActionExcute;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hy | Anim")
	TObjectPtr<class UHyAnimInstance> HyAnimInstance;


protected:
	// BlueprintSetting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Init")
	FCharacterDefaultTagSet CharacterDefaultTagSet;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Input")
	FCharacterInputData CharacterInputData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FCharacterStateData CharacterStateData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FCharacterCombatDataSet CharacterCombatDataSet;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Debug")
	FCharacterDebugData CharacterDebugData;
	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	FGameplayTag CharacterTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hy | Character")
	EHyAttackTrailType AttackTrailType;

	FGuid MyGuid;
	FGuid TargetGuid;

	int32 SpawnID = 0;
	FVector LastAttackDirection;
public:
	// TODO TEMP
	TQueue<ECombatDirection> CombatArrowQueue;

	const float DashAttackRange = 700.f;
	const float EnableTargetRange = 1000.f;
	const float AirAttackHeight = 750.f;

	float KeepDownTime = 0.0f;

};
