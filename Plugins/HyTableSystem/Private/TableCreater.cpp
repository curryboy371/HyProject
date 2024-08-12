// Fill out your copyright notice in the Description page of Project Settings.


#include "TableCreater.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "EditorFramework/AssetImportData.h"
#include "UObject/SavePackage.h"
#include "UObject/UObjectIterator.h"

void UTableCreater::CreateTable(bool forceupdate)
{
#if WITH_EDITOR
	for (TObjectIterator<UScriptStruct> It; It; ++It)
	{
		UScriptStruct* Struct = *It;
		
		if(Struct->HasMetaData(UTableCreater::GetMetaKey()) == true)
		{
			FString value = Struct->GetMetaData(UTableCreater::GetMetaKey());
			//if(value == TEXT("TableEntity"))
			if(value == UTableCreater::GetMetaValue())
			{
				CreateTableUasset(Struct, forceupdate);
				GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error,
                		 	FString::Printf(TEXT("Not Loading %s"), *Struct->GetName()));
			}
		}
	}
#endif
}

void UTableCreater::CreateTableUasset(UScriptStruct* srtucttarget, bool forceupdate)
{
#if WITH_EDITOR

	// ex> Character_TableEntity
	FString assetname = srtucttarget->GetName().Replace(TEXT("Entity"), TEXT(""));
	// 데이타테이블 존재 체크하기
	FString filecheckpath = FString::Printf(TEXT("%sTableData/%s.uasset"), *FPaths::ProjectContentDir(), *assetname);
	if(FPaths::FileExists(filecheckpath) == true
		&& forceupdate == false)
	{
		return;
	}
	
	// csv 경로
	FString assetpath = FString::Printf(TEXT("Content/AssetSource/table/%s.csv"), *assetname);
	FString filepath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() + assetpath);
	FString data;
	if(FFileHelper::LoadFileToString(data, *filepath) == false)
	{
		GLog->Log(TEXT("TableCreater"), ELogVerbosity::Type::Log
				, FString::Printf(TEXT("Create %s error Not Find CSV File : %s"), *assetname, *filepath));
	}
	
	
	// 테이블 저장경로는 고정임
	FString packagename = FString::Printf(TEXT("/Game/TableData/%s"), *assetname);
	UPackage* package = CreatePackage(*packagename);
	package->FullyLoad();
	UDataTable* datatable = NewObject<UDataTable>(
		package, *assetname, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	if(nullptr == datatable)
	{
		return;
	}

	datatable->RowStruct = srtucttarget;
	TArray<FString> importresult = datatable->CreateTableFromCSVString(data);
	for(int it = 0 ; it < importresult.Num();it++)
	{
		GLog->Log(TEXT("TableCreater"), ELogVerbosity::Type::Log
			, FString::Printf(TEXT("Create %s error %s"), *assetname, *importresult[it]));
	}
	assetpath = FString::Printf(TEXT("../../AssetSource/table/%s.csv"), *assetname);
	datatable->AssetImportData->Update(assetpath);
	
	if(package->MarkPackageDirty() == false)
	{
	}
	FAssetRegistryModule::AssetCreated(datatable);
	FString packagefilename = FPackageName::LongPackageNameToFilename(
		packagename, FPackageName::GetAssetPackageExtension());
	
	FSavePackageArgs args = FSavePackageArgs();
	args.TopLevelFlags = RF_Public | RF_Standalone;
	args.Error = GError;
	args.bForceByteSwapping = true;
	args.bWarnOfLongFilename = SAVE_NoError;	
	bool saved = UPackage::SavePackage(
	package, datatable, *packagefilename, args);
#endif	
}
