// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "HyTableTypes.h"

#include "HyTableSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HYTABLE_API UHyTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

public:
	// TODO Table Generator
	void CreateHyTable() {};
	void CreateHyTableUasset(UScriptStruct* InStruct) {};

	// Table Loader
	template<class T>
	bool GetTableAll(TArray<T*>& OutTableEntitys)
	{
		FString StructName = T::StaticStruct()->GetName();
		FString TableName = MakeStructNameToTableName(StructName);
		FString TablePath = MakeResourcePath(TableName);
		FName TableNameKey = *TableName;

		UDataTable* DataTable = CheckOrAddTableData(TableNameKey, TablePath, TableName);
		if (!DataTable)
		{
			return false;
		}

		TArray<FName> RowNames = DataTable->GetRowNames();
		for (const FName& RowName : RowNames)
		{
			T* RowData = DataTable->FindRow<T>(RowName, FString(), false);
			if (RowData)
			{
				OutTableEntitys.Add(RowData);
			}
		}
		return true;
	}

	template<class T>
	bool GetTableData(int32 Index, T& OutTableEntity)
	{
		if (Index <= 0)
		{
			return false;
		}

		FString StructName = T::StaticStruct()->GetName();
		FString TableName = MakeStructNameToTableName(StructName);
		FString TablePath = MakeResourcePath(TableName);
		FName TableNameKey = *TableName;
	
		UDataTable* DataTable = CheckOrAddTableData(TableNameKey, TablePath, TableName);
		if (!DataTable)
		{
			return false;
		}
	
		FName RowName = FName(*FString::FromInt(Index));
		T* RowData = DataTable->FindRow<T>(RowName, FString());
		if (RowData)
		{
			OutTableEntity = *RowData;
			return true;
		}
	
		return false;
	}

	template<class T>
	T* GetTableData(int32 Index)
	{
		if (Index <= 0) return nullptr;
	
		FString StructName = T::StaticStruct()->GetName();
		FString TableName = MakeStructNameToTableName(StructName);
		FString TablePath = MakeResourcePath(TableName);
		FName TableNameKey = *TableName;
	
		UDataTable* DataTable = CheckOrAddTableData(TableNameKey, TablePath, TableName);
		if (!DataTable)
		{
			return false;
		}

		FName RowName = FName(*FString::FromInt(Index));
		return DataTable->FindRow<T>(RowName, TableName, false);
	}


protected:
	UDataTable* CheckOrAddTableData(FName& Tablenamekey, FString& TablePath, FString& TableName)
	{
		if (!HyTableDataMap.Contains(Tablenamekey))
		{
			AddTableData(Tablenamekey, TablePath);

			if (!HyTableDataMap.Contains(Tablenamekey))
			{
				GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Failed to load table data for %s"), *TableName));
				return nullptr;
			}
		}

		if (!HyTableDataMap[Tablenamekey]->DataTable)
		{
			GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Failed to load table data for %s"), *TableName));

			HyTableDataMap.Remove(Tablenamekey);
			return nullptr;
		}

		return HyTableDataMap[Tablenamekey]->DataTable;
	}

	void AddTableData(FName& InTablenamekey, FString& InTablePath)
	{
		HyTableDataMap.Add(InTablenamekey, nullptr);
		HyTableDataMap[InTablenamekey] = NewObject<UHyDataTable>();
		HyTableDataMap[InTablenamekey]->AddToRoot(); // GC가 Table객체를 수집하지 않도록 보호
		HyTableDataMap[InTablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *InTablePath, NULL, LOAD_None, NULL);
	}

	FString MakeResourcePath(FString InFileStr)
	{
		return FString::Printf(TEXT("DataTable'/HyTable/TableData/%s.%s'"), *InFileStr, *InFileStr);
	}

	PRAGMA_DISABLE_OPTIMIZATION
	// 이 사이에 있는 코드는 최적화가 금지되어 브레이크 포인트를 걸 수 있다.
	FString MakeStructNameToTableName(FString InStructName)
	{
		int32 Length = InStructName.Len();

		// 뒤에서부터 처음 발견된 _ 를 찾는다.
		int32 UnderbarIdx = InStructName.Find(FString("_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd, Length);
		if (UnderbarIdx == -1)
		{
			UnderbarIdx = 0;
		}

		FString TableName = InStructName.Left(UnderbarIdx);

		return FString::Printf(TEXT("%s_%s"), *TableName, TEXT("Table"));
	}
	PRAGMA_ENABLE_OPTIMIZATION

protected:
	UPROPERTY()
	TMap<FName, UHyDataTable*> HyTableDataMap; // <TableName, HyTable>

};
