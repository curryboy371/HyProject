// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HyCollisionSystemComponent.h"

#include "HyCoreMacro.h"

#include "GameFramework/Character.h"

#include "Components/HyInventorySystemComponent.h"

#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

#include "HyCoreFunctionLibrary.h"

#include "HyCoreDeveloperSettings.h"

#include "HyTagSubsystem.h"

#include "Items/HyWeapon.h"
#include "InvenTypes.h"
#include "Table/Item_TableEntity.h"
#include "GameplayTagContainer.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>


UHyCollisionSystemComponent::UHyCollisionSystemComponent()
{
	CharacterOwner = nullptr;
	PrimaryComponentTick.bCanEverTick = true;


}

void UHyCollisionSystemComponent::InitializeHyActorComponent()
{
	Super::InitializeHyActorComponent();

	ColliderTraceSetup();
}

void UHyCollisionSystemComponent::SetEquipWeapon(const FGameplayTag& InEquipTag, const bool bCombatMode)
{
	if (!InventorySystemComp)
	{
		ERR_V("Invalid InventorySystemComp");
		return;
	}

	// 기존 Weapon Tag제거
	if (CurEquipWeaponTag != FGameplayTag::EmptyTag)
	{
		if (FColliderTraceInfo* UnEquipWeaponInfo = AttackColliderTraceInsts.FindByKey(CurEquipWeaponTag))
		{
			UnEquipWeaponInfo->bEnableCollider = false;
			CurEquipWeaponTag = FGameplayTag::EmptyTag;
		}
	}

	if (bCombatMode)
	{
		// 새로운 WeaponTag 추가
		TObjectPtr<AHyWeapon> EquipWeapon = InventorySystemComp->GetEquippedWeapon();
		if (!EquipWeapon)
		{
			ERR_V("Invalid EquipWeapon");
			return;
		}

		const FItem_TableEntity& ItemTableInfo = EquipWeapon->GetItemTableInfo();

		FColliderTraceInfo ColliderInfo;
		ColliderInfo.TagName = ItemTableInfo.WeaponCollider;
		ColliderInfo.EndSocket = ItemTableInfo.EndSocketName;
		ColliderInfo.StartSocket = ItemTableInfo.StartSocketName;
		ColliderInfo.Radius = ItemTableInfo.WeaponRadius;
		ColliderInfo.Height = ItemTableInfo.WeaponHeight;
		ColliderInfo.bIsWeaponCollider = true;

		EWeaponMeshType EquipWeaponMeshType = EquipWeapon->GetWeaponMeshType();

		switch (EquipWeaponMeshType)
		{
		case EWeaponMeshType::EWeaponMesh_StaticMesh:

			break;

		case EWeaponMeshType::EWeaponMesh_SkeletalMesh:
		{
			if (const USkeletalMeshComponent* WeaponSkeletalMesh = EquipWeapon->GetMeshComponent())
			{
				if (WeaponSkeletalMesh->DoesSocketExist(ColliderInfo.StartSocket) == false)
				{
					ERR_V("Invalid Bone Socket Name %s", *ColliderInfo.StartSocket.ToString());
					return;
				}

				if (WeaponSkeletalMesh->DoesSocketExist(ColliderInfo.EndSocket) == false)
				{
					ERR_V("Invalid Bone Socket Name %s", *ColliderInfo.EndSocket.ToString());
					return;
				}

				if (ColliderInfo.Radius <= 0.f)
				{
					ERR_V("Invalid Radius");
					return;
				}

				if (ColliderInfo.Height <= 0.f)
				{
					ERR_V("Invalid Height");
					return;
				}

			}
		}
		break;

		default:
			break;
		}

		CurEquipWeaponTag = ColliderInfo.TagName;
		ColliderInfo.bEnableCollider = true;
		AttackColliderTraceInsts.Add(ColliderInfo);

	}

}

void UHyCollisionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UHyCollisionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bOnAttack)
	{
		UpdateTraceSweep();
	}

	DebugDrawCharacterCapsule();
}

void UHyCollisionSystemComponent::EnableAttackCollider(const FAttackCollisionSettings& InAttackCollisionSet)
{
	if (!CharacterOwner)
	{
		ERR_V("Invalid CharacterOwner");
		return;
	}

	CurAttackCollisionSet = InAttackCollisionSet;
	bOnAttack = true;
	bSucessHit = false;
	AttackCompletionTags.Empty();
	ResetIgnoreActors();


	if (!InventorySystemComp)
	{
		ERR_V("Invalid InventorySystemComp");
		return;
	}

	TObjectPtr<AHyWeapon> EquipWeapon = InventorySystemComp->GetEquippedWeapon();
	if (!EquipWeapon)
	{
		ERR_V("Invalid EquipWeapon");
		return;
	}

	EquipWeapon->ActiveTrail(true);
}

void UHyCollisionSystemComponent::DisableAttackCollider()
{
	bOnAttack = false;
	bSucessHit = false;
	AttackCompletionTags.Empty();


	ResetIgnoreActors();

	if (!InventorySystemComp)
	{
		ERR_V("Invalid InventorySystemComp");
		return;
	}

	TObjectPtr<AHyWeapon> EquipWeapon = InventorySystemComp->GetEquippedWeapon();
	if (!EquipWeapon)
	{
		ERR_V("Invalid EquipWeapon");
		return;
	}

	EquipWeapon->ActiveTrail(false);
}

void UHyCollisionSystemComponent::ColliderTraceSetup()
{
	// TODO Tool에서 제작하여 저장하는 형식으로 변경해서 사용되어야함
	// Character BP에서 추가한 AttackColliderTrace를 검증하여 InstMap에 추가

	if (!CharacterOwner)
	{
		ERR_V("Invalid CharacterOwner");
		return;
	}

	InventorySystemComp = CharacterOwner->FindComponentByClass<UHyInventorySystemComponent>();

	if (!InventorySystemComp)
	{
		ERR_V("Invalid InventorySystemComp");
		return;
	}


	for (const auto& ColliderInfo : AttackColliderTraces)
	{
		if (AttackColliderTraceInsts.Contains(ColliderInfo))
		{
			ERR_V("Already Exist Collider Info %s", *ColliderInfo.TagName.ToString());
			continue;
		}

		if (!CharacterOwner->GetMesh())
		{
			ERR_V("Invalid CharacterOwner Mesh");
			continue;
		}

		if (CharacterOwner->GetMesh()->DoesSocketExist(ColliderInfo.StartSocket) == false)
		{
			ERR_V("Invalid Bone Socket Name %s", *ColliderInfo.StartSocket.ToString());
			continue;
		}

		if (CharacterOwner->GetMesh()->DoesSocketExist(ColliderInfo.EndSocket) == false)
		{
			ERR_V("Invalid Bone Socket Name %s", *ColliderInfo.EndSocket.ToString());
			continue;
		}

		if (ColliderInfo.Radius <= 0.f)
		{
			ERR_V("Invalid Radius");
			continue;
		}

		if (ColliderInfo.Height <= 0.f)
		{
			ERR_V("Invalid Height");
			continue;
		}

		AttackColliderTraceInsts.Add(ColliderInfo);
	}

}

void UHyCollisionSystemComponent::UpdateTraceSweep()
{
	if (!CharacterOwner)
	{
		ERR_V("Invalid CharacterOwner");
		return;
	}

	if (!InventorySystemComp)
	{
		ERR_V("Invalid InventorySystemComp");
		return;
	}

	TObjectPtr<USkeletalMeshComponent> MeshComp = CharacterOwner->GetMesh();
	if(!MeshComp)
	{
		ERR_V("Invalid MeshComp");
		return;
	}

	int32 RemainAttackableCount = (CurAttackCollisionSet.AttackableUnitCount == 0) ? MAX_ATTACKABLE_COUNT : CurAttackCollisionSet.AttackableUnitCount;

	for (const FGameplayTag& ColliderTag : CurAttackCollisionSet.AttackColliderTags)
	{
		// 공격 가능한 유닛 초과
		if (RemainAttackableCount <= 0)
		{
			break;
		}

		// 이미 공격이 완료된 Collider Tag 체크
		if(AttackCompletionTags.Contains(ColliderTag))
		{
			continue;
		}

		if (FColliderTraceInfo* ColliderTraceInfo = AttackColliderTraceInsts.FindByKey(ColliderTag))
		{
			if (!ColliderTraceInfo->bEnableCollider)
			{
				continue;
			}


			FVector StartLocation;
			FVector EndLocation;

			if (ColliderTraceInfo->bIsWeaponCollider)
			{
				// 새로운 WeaponTag 추가
				TObjectPtr<AHyWeapon> EquipWeapon = InventorySystemComp->GetEquippedWeapon();
				if (!EquipWeapon)
				{
					ERR_V("Invalid EquipWeapon");
					continue;
				}

				EWeaponMeshType EquipWeaponMeshType = EquipWeapon->GetWeaponMeshType();

				switch (EquipWeaponMeshType)
				{
				case EWeaponMeshType::EWeaponMesh_StaticMesh:
					break;

				case EWeaponMeshType::EWeaponMesh_SkeletalMesh:
				{
					if (const USkeletalMeshComponent* WeaponSkeletalMesh = EquipWeapon->GetMeshComponent())
					{
						StartLocation = WeaponSkeletalMesh->GetSocketLocation(ColliderTraceInfo->StartSocket);
						EndLocation = WeaponSkeletalMesh->GetSocketLocation(ColliderTraceInfo->EndSocket);
						
					}
					else
					{
						ERR_V("Invalid WeaponSkeletalMesh");
						continue;
					}
				}
				break;
				}
			}
			else
			{
				StartLocation = MeshComp->GetSocketLocation(ColliderTraceInfo->StartSocket);
				EndLocation = MeshComp->GetSocketLocation(ColliderTraceInfo->EndSocket);

			}


			FTraceData TraceData(StartLocation, EndLocation, ColliderTraceInfo->Radius, ColliderTraceInfo->Height);

			FHitResult HitResult;
			bool bRes = SweepSingle(TraceData, CollisionMainParams, false, HitResult);
			if (bRes)
			{
				CollisionMainParams.AddIgnoredActor(HitResult.GetActor()); // 이미 충돌 시도한 객체는 더이상 충돌하지 않도록
			
				if (TakeDamage(ColliderTag, CurAttackCollisionSet.TagName, HitResult))
				{
					ApplyAttackImpact(HitResult, CurAttackCollisionSet);
					AttackCompletionTags.Add(ColliderTag);
					--RemainAttackableCount;
					bSucessHit = true;
				}
			}
			//	else if (!ColliderTraceInfo->bIsFirstFrame && ColliderTraceInfo->bCrossframeAccuracy) // 첫 프레임이 아니면서 충돌 보완on이면 보간
			//	{
			//		if (ColliderTraceInfo->Radius > 0)
			//		{
			//
			//
			//			FVector StartDiff = StartLocation - ColliderTraceInfo->PreStartSocketPos;
			//			FVector EndDiff = EndLocation - ColliderTraceInfo->PreEndSocketPos;
			//
			//			FVector Diff = StartDiff.Size() > EndDiff.Size() ? StartDiff : EndDiff;
			//
			//			int32 LerpCount = FMath::RoundToInt32(Diff.Size() / (ColliderTraceInfo->Radius * 2.f));
			//
			//			float AlphaRatio = 1.f / static_cast<float>(LerpCount + 1); // 보간 카운트를 alpha ratio로 변환
			//
			//			LOG_V("Lerp Diff %f  radius  %f LerpCount %d  AlphaRatio %f", Diff.Size(), ColliderTraceInfo->Radius, LerpCount, AlphaRatio);
			//
			//			if (LerpCount > 0)
			//			{
			//				for (int32 i = 1; i <= LerpCount; ++i)
			//				{
			//					float Alpha = AlphaRatio * i;
			//					FVector LerpStartPos = FMath::Lerp(ColliderTraceInfo->PreStartSocketPos, StartLocation, Alpha);
			//					FVector LerpEndPos = FMath::Lerp(ColliderTraceInfo->PreEndSocketPos, EndLocation, Alpha);
			//
			//					TraceData = FTraceData(LerpStartPos, LerpEndPos, ColliderTraceInfo->Radius);
			//
			//					bRes = SweepSingle(TraceData, CollisionMainParams, true, HitResult);
			//					if (bRes)
			//					{
			//						CollisionMainParams.AddIgnoredActor(HitResult.GetActor()); // 이미 충돌 시도한 객체는 더이상 충돌하지 않도록
			//
			//						if (TakeDamage(ColliderTag, CurAttackCollisionSet.HitTag, HitResult))
			//						{
			//							ApplyAttackImpact(HitResult, CurAttackCollisionSet);
			//							FinishAttackTags.Add(ColliderTag);
			//							bSucessHit = true;
			//							break;
			//						}
			//					}
			//					UNPFunctionLib::DrawPointer(GetWorld(), LerpStartPos, 5, FLinearColor::Red, 3);
			//					UNPFunctionLib::DrawPointer(GetWorld(), LerpEndPos, 5, FLinearColor::Black, 3);
			//
			//					LOG_V("Lerp Alpha %f", Alpha);
			//				}
			//			}
			//		}
			//	}
			//}
			//else
			//{
			//	// 멀티 attack 충돌 체크
			//	TArray<FHitResult> HitResults;
			//	bool bRes = SweepMulti(TraceData, CollisionMainParams, false, HitResults);
			//	if (bRes)
			//	{
			//		for (FHitResult& HitResult : HitResults)
			//		{
			//			CollisionMainParams.AddIgnoredActor(HitResult.GetActor()); // 이미 충돌 시도한 객체는 더이상 충돌하지 않도록
			//
			//			if (TakeDamage(ColliderTag, CurAttackCollisionSet.HitTag, HitResult))
			//			{
			//				ApplyAttackImpact(HitResult, CurAttackCollisionSet);
			//				bSucessHit = true;
			//			}
			//		}
			//	}
			//
			//}

			ColliderTraceInfo->bIsFirstFrame = false;
			ColliderTraceInfo->PreStartSocketPos = StartLocation;
			ColliderTraceInfo->PreEndSocketPos = EndLocation;
		}
	}
}

bool UHyCollisionSystemComponent::SweepSingle(const FTraceData& InTraceData, const FCollisionQueryParams& InCollisionParams, const bool bIsLerpSweep, FHitResult& OutHitResult)
{
	bool bHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		InTraceData.StartLocation,
		InTraceData.EndLocation,
		InTraceData.DiffTraceRotation.Quaternion(),
		CCHANNEL_HYATTACK,
		FCollisionShape::MakeSphere(InTraceData.TraceRadius),
		InCollisionParams
	);

	FVector CapsuleLocation = InTraceData.StartLocation + (InTraceData.DiffTrace) * 0.5f;

	FQuat Quat = FRotationMatrix::MakeFromZ(InTraceData.DiffTrace).ToQuat();


	bool bDebugDrawCollider = false;
	if (UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSettingRef())
	{
		if (DevSetting->IsDebugDrawCollision())
		{
			bDebugDrawCollider = true;
		}
	}


	if (!bIsLerpSweep)
	{
		if (bHit)
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Red, 1, 1);
			}
		}
		else
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Yellow, 1, 1);
			}
		}
	}
	else
	{
		if (bHit)
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Black, 1, 1);
			}
		}
		else
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Green, 1, 1);
			}
		}
	}

	return bHit;
}

bool UHyCollisionSystemComponent::SweepMulti(const FTraceData& InTraceData, const FCollisionQueryParams& InCollisionParams, const bool bIsLerpSweep, TArray<FHitResult>& OutHitResults)
{
	OutHitResults.Reset();

	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHitResults,
		InTraceData.StartLocation,
		InTraceData.EndLocation,
		InTraceData.DiffTraceRotation.Quaternion(),
		CCHANNEL_HYATTACK,
		FCollisionShape::MakeSphere(InTraceData.TraceRadius),
		InCollisionParams
	);

	FVector CapsuleLocation = InTraceData.StartLocation + (InTraceData.DiffTrace) * 0.5f;

	FQuat Quat = FRotationMatrix::MakeFromZ(InTraceData.DiffTrace).ToQuat();


	bool bDebugDrawCollider = false;
	if (UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSettingRef())
	{
		if (DevSetting->IsDebugDrawCollision())
		{
			bDebugDrawCollider = true;
		}
	}

	if (!bIsLerpSweep)
	{
		if (bHit)
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Red, 1, 1);
			}
		}
		else
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Yellow, 1, 1);
			}
		}
	}
	else
	{
		if (bHit)
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Black, 1, 1);
			}
		}
		else
		{
			if (bDebugDrawCollider)
			{
				UHyCoreFunctionLibrary::DrawCapsuleQuat(GetWorld(), CapsuleLocation, InTraceData.TraceHeight * 0.5, InTraceData.TraceRadius, Quat, FColor::Green, 1, 1);
			}
		}
	}


	return bHit;
}

bool UHyCollisionSystemComponent::TakeDamage(const FGameplayTag& InAttackCollisionTag, const FGameplayTag& InHitTag, const FHitResult& InHitResult)
{
	if (!CharacterOwner)
	{
		return false;
	}

	UHyTagSubsystem* TagSubSystem = GET_TAG_SUBSYSTEM();
	if (!TagSubSystem)
	{
		return false;
	}

	TObjectPtr<AActor> TargetActor = InHitResult.GetActor();
	if (!TargetActor)
	{
		return false;
	}

	FVector AttackDirection = TargetActor->GetActorLocation() - CharacterOwner->GetActorLocation();
	AttackDirection = AttackDirection.GetSafeNormal2D();
	// Target의 로컬 좌표계에서의 AttackDirection 계산
	// LocalAttackDirection : Attacker 위치를  기준으로 타겟이 밀려나는 방향 벡터
	FVector TargetForward = TargetActor->GetActorForwardVector();
	float DotProduct = FVector::DotProduct(AttackDirection, TargetForward);
	FVector CrossProduct = FVector::CrossProduct(TargetForward, AttackDirection);

	FHyDamageEvent DamageEvent;
	DamageEvent.HitTag = InHitTag;
	DamageEvent.SetHitResult(InHitResult);
	DamageEvent.AttackDirection = AttackDirection;

	if (TagSubSystem->IsCriticalHit(InHitTag))
	{
		DamageEvent.DamageType = EHyDamageType::EHyDamage_Critical;

		// 타겟의 방향벡터와 LocalAttackDirection가 일치해야 백어택. 
		if(DotProduct > 0.2f)
		{
			DamageEvent.ActionContext = TEXT("Back");
			DamageEvent.DownTime = 5.f;
		}
	}
	else if (TagSubSystem->IsLargeHit(InHitTag))
	{
		DamageEvent.DamageType = EHyDamageType::EHyDamage_Large;
	}
	else if (TagSubSystem->IsNormalHit(InHitTag))
	{
		DamageEvent.DamageType = EHyDamageType::EHyDamage_Normal;

		if (DotProduct > 0.7f)
		{
			DamageEvent.ActionContext = TEXT("Back");
		}
		else
		{
			if (DotProduct < -0.8f)
			{
				DamageEvent.ActionContext = TEXT("Forward");
			}
			else if(DotProduct < -0.5f)
			{
				if (CrossProduct.Z > 0.0f)
				{
					DamageEvent.ActionContext = TEXT("ForwardRight");
				}
				else
				{
					DamageEvent.ActionContext = TEXT("ForwardLeft");
				}
			}
			else
			{
				if (CrossProduct.Z > 0.0f)
				{
					DamageEvent.ActionContext = TEXT("Right");
				}
				else
				{
					DamageEvent.ActionContext = TEXT("Left");
				}
			}
		}

	}

	int32 DamageAmount = FMath::RandRange(10, 100); // TODO TEMP;

	//LOG_V("DotProduct %f CrossProduct Z %f %s", DotProduct, CrossProduct.Z, *DamageEvent.ActionContext);
	InHitResult.GetActor()->TakeDamage(DamageAmount, DamageEvent, CharacterOwner->GetController(), CharacterOwner);
	return true;
}

void UHyCollisionSystemComponent::ApplyAttackImpact(FHitResult& HitResult, const FAttackCollisionSettings& InAttackCollisionSettings)
{
	if (!CharacterOwner)
	{
		return;
	}

	// 첫 타격에서만
	if (!bSucessHit)
	{
		// local player
		if (CharacterOwner->GetController() == GetWorld()->GetFirstPlayerController())
		{
			if (InAttackCollisionSettings.CameraShakeSettings.CameraShake)
			{
				const FCameraShakeSettings& CameraSetting = InAttackCollisionSettings.CameraShakeSettings;
				
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraSetting.CameraShake, HitResult.ImpactPoint, 0.f, CameraSetting.CameraShakeRadius);
			}

		}

	}


}

void UHyCollisionSystemComponent::ResetIgnoreActors()
{
	CollisionMainParams.ClearIgnoredActors();
	CollisionMainParams.AddIgnoredActor(GetOwner());
}

void UHyCollisionSystemComponent::DebugDrawCharacterCapsule()
{
	if (UHyCoreDeveloperSettings* DevSetting = UHyCoreDeveloperSettings::GetDeveloperSettingRef())
	{
		if (DevSetting->IsDebugDrawCollision())
		{
			if (CharacterOwner && CharacterOwner->GetCapsuleComponent())
			{
				FVector CapsuleLocation = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
				float CapsuleRadius = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
				float CapsuleHalfHeight = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
				FRotator CapsuleRotation = CharacterOwner->GetCapsuleComponent()->GetComponentRotation();

				UHyCoreFunctionLibrary::DrawCapsule(GetWorld(), CapsuleLocation, CapsuleHalfHeight, CapsuleRadius, CapsuleRotation, FColor::Black, 0.0f, 0.5f);
			}

		}
	}
}
