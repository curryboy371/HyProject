// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource/HyResourceLoadSubsystem.h"

FResourceloaderArgument::~FResourceloaderArgument()
{
	if (ObjectPtr != nullptr)
	{
		ObjectPtr->RemoveFromRoot();
	}
}

void FResourceloaderArgument::SetObjectPtr(UObject* InObject)
{
	ObjectPtr = InObject;
	if (ObjectPtr != nullptr)
	{
		// GC가 제거 못하도록
		ObjectPtr->AddToRoot();
	}
}


void UHyResourceLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UHyResourceLoadSubsystem::Deinitialize()
{
}

void UHyResourceLoadSubsystem::LoadMemoryAsync(const FName& InPath, FResourceloaderArgument* InArg, FResourceLoaderAsyncDelegate DelegateToCall)
{
	if (InPath == NAME_None)
	{
		ERR_V("UResourceLoader.LoadMemoryAsyncT(%s), InPath == NAME_None", *InPath.ToString());
		InArg->bIsError = true;
		DelegateToCall.ExecuteIfBound(InArg);
		return;
	}

	// 리소스 경로 체크
	if (CheckVaildPath(InPath) == false)
	{
		ERR_V("UResourceLoader.LoadMemoryAsyncT(%s), InPath is not valied.", *InPath.ToString());
		InArg->bIsError = true;
		DelegateToCall.ExecuteIfBound(InArg);
		return;
	}

	FName Path = InPath;

	// 비동기 로드
	UAssetManager::GetStreamableManager().RequestAsyncLoad(FSoftObjectPath(Path.ToString()),
		FStreamableDelegate::CreateLambda(
			[](const FName& local_Path, FResourceloaderArgument* local_Arg, FResourceLoaderAsyncDelegate local_DelegateToCall)
			{
				// already loaded, just find UClass ptr
				UClass* GeneratedTemplate = (UClass*)StaticLoadObject(UClass::StaticClass(), nullptr, *local_Path.ToString(), nullptr, LOAD_None, nullptr);
				if (GeneratedTemplate == nullptr)
				{
					ERR_V("UResourceLoader.LoadMemoryAsyncT(%s), GeneratedClass == nullptr", *local_Path.ToString());
					local_Arg->bIsError = true;
				}
				else
				{
					local_Arg->SetObjectPtr(GeneratedTemplate);
				}

				local_DelegateToCall.ExecuteIfBound(local_Arg);
			},
			Path,
			InArg,
			DelegateToCall
		)
	);
}

const bool UHyResourceLoadSubsystem::CheckVaildPath(const FName& InPath) const
{
	return true;
}

const bool UHyResourceLoadSubsystem::FileExists(const FName& InPath) const
{
	return true;
}


