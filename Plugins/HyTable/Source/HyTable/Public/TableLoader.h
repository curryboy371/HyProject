// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HyDataTable.h"
#include "UObject/Object.h"
#include "TableLoader.generated.h"

/**
 * 
 */
UCLASS()
class HYTABLE_API UTableLoader : public UObject
{
	GENERATED_BODY()	
public:
	static UTableLoader* Get()
	{
		static TWeakObjectPtr<UTableLoader> TableLoaderInstance;
		if (false == TableLoaderInstance.IsValid())
		{
			TableLoaderInstance = NewObject<UTableLoader>();
			TableLoaderInstance->AddToRoot();
		}
		if (TableLoaderInstance.IsValid())
		{
			return TableLoaderInstance.Get();
		}
		return nullptr;
	}

	template<class T>
	static bool Get_Table_All(TArray<T*>& OutTableEntitys)
	{
		FString TableName = MakeStructNameToTableName(T::StaticStruct()->GetName());
		FString TablePath = MakeResourcePath(TableName);
		FName Tablenamekey = *TableName;
	
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
			Get()->TableInstanceMap[Tablenamekey] = NewObject<UHyDataTable>();
			Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
			Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
		}
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			return false;
		}
		if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
		{
			GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
			Get()->TableInstanceMap.Remove(Tablenamekey);
			return false;
		}
		
		TArray<FName> names=Get()->TableInstanceMap[Tablenamekey]->DataTable->GetRowNames();
		for(int32 Index = 0; Index < names.Num(); ++Index)
		{
			OutTableEntitys.Add(Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(names[Index], FString(""), false));
		}
		return true;
	}

	template<class T>
	static bool Get_Table_Data(int index, T& OutTableEntitys)
	{
		if(index<=0) return false;

		FString TableName = MakeStructNameToTableName(T::StaticStruct()->GetName());
		FString TablePath = MakeResourcePath(TableName);
		FName Tablenamekey = *TableName;
	
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
			Get()->TableInstanceMap[Tablenamekey] = NewObject<UHyDataTable>();
			Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
			Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
		}
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			return false;
		}
		if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
		{
			GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
			Get()->TableInstanceMap.Remove(Tablenamekey);
			return false;
		}
	
		FName RowName = FName(*FString::FromInt(index));
		T* FindTable = Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(RowName, FString(""), false);
		if(FindTable)
		{
			OutTableEntitys = *FindTable;
			return true;
		}
		return false;
	}
	
	template<class T>
	static T* Get_Table_Data(int index)
	{
		if(index<=0) return nullptr;
		
		FString TableName = MakeStructNameToTableName(T::StaticStruct()->GetName());
		FString TablePath = MakeResourcePath(TableName);
		FName Tablenamekey = *TableName;

		FString TestName = MakeStructNameToTableName(TEXT("asd_asd_asq_a"));
		
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
			Get()->TableInstanceMap[Tablenamekey] = NewObject<UHyDataTable>();
			Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
			Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
		}
		if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
		{
			return nullptr;
		}
		if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
		{
			GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
			Get()->TableInstanceMap.Remove(Tablenamekey);
			return nullptr;
		}
		
		FName RowName = FName(*FString::FromInt(index));
		//FName RowName = FName(TEXT("CLVL1"));
		T* FindTable = Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(RowName, TableName, false);
		return FindTable;
	}
	
	static FString MakeResourcePath(FString filename)
	{
		return FString::Printf(TEXT("DataTable'/Game/TableData/%s.%s'"),*filename, *filename);
	}

	PRAGMA_DISABLE_OPTIMIZATION
	// 이 사이에 있는 코드는 최적화가 금지되어 브레이크 포인트를 걸 수 있다.
	static FString MakeStructNameToTableName(FString classname)
	{
		FString fieldname = classname;

		int index = fieldname.Len();
		{
			// 뒤에서부터 처음 발견된 _ 를 찾는다.
			int searindex = fieldname.Find(FString("_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd, index);
			if(searindex != -1)
			{
				index = searindex;
			}
		}

		FString leftname = fieldname.Left(index);

		return FString::Printf(TEXT("%s_%s"), *leftname, TEXT("Table")); 
	}
	PRAGMA_ENABLE_OPTIMIZATION

protected:	
	UPROPERTY()
	TMap<FName, UHyDataTable*> TableInstanceMap;
};