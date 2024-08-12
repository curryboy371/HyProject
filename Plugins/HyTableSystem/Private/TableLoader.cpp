// Fill out your copyright notice in the Description page of Project Settings.


#include "TableLoader.h"

// template <typename T>
// bool UTableLoader::Get_Table_All(FString TableName, TArray<T*>& OutTableEntitys)
// {
// 	FString TablePath = MakeResourcePath(TableName);
// 	FName Tablenamekey = *TableName;
//
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
// 		Get()->TableInstanceMap[Tablenamekey] = NewObject<UNPDataTable>();
// 		Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
// 		Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
// 	}
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		return false;
// 	}
// 	if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
// 	{
// 		GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
// 		Get()->TableInstanceMap.Remove(Tablenamekey);
// 		return false;
// 	}
// 	
// 	TArray<FName> names=Get()->TableInstanceMap[Tablenamekey]->DataTable->GetRowNames();
// 	for(int32 Index = 0; Index < names.Num(); ++Index)
// 	{
// 		OutTableEntitys.Add(Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(names[Index], FString(""), false));
// 	}
// 	return true;
// }
//
// template <typename T>
// bool UTableLoader::Get_Table_Data(FString TableName, int index, T& OutTableEntitys)
// {
// 	if(index<=0) return false;
// 	
// 	FString TablePath = MakeResourcePath(TableName);
// 	FName Tablenamekey = *TableName;
//
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
// 		Get()->TableInstanceMap[Tablenamekey] = NewObject<UNPDataTable>();
// 		Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
// 		Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
// 	}
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		return false;
// 	}
// 	if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
// 	{
// 		GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
// 		Get()->TableInstanceMap.Remove(Tablenamekey);
// 		return false;
// 	}
//
// 	FName RowName = FName(*FString::FromInt(index));
// 	T* FindTable = Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(RowName, FString(""), false);
// 	if(FindTable)
// 	{
// 		OutTableEntitys = *FindTable;
// 		return true;
// 	}
// 	return false;
// }

// template <class T>
// T* UTableLoader::Get_Table_Data(FString TableName, int index)
// {
// 	if(index<=0) return nullptr;
// 	
// 	FString TablePath = MakeResourcePath(TableName);
// 	FName Tablenamekey = *TableName;
//
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		Get()->TableInstanceMap.Add(Tablenamekey, nullptr);
// 		Get()->TableInstanceMap[Tablenamekey] = NewObject<UNPDataTable>();
// 		Get()->TableInstanceMap[Tablenamekey]->AddToRoot();
// 		Get()->TableInstanceMap[Tablenamekey]->DataTable = LoadObject<UDataTable>(NULL, *TablePath, NULL, LOAD_None, NULL);
// 	}
// 	if(false == Get()->TableInstanceMap.Contains(Tablenamekey))
// 	{
// 		return nullptr;
// 	}
// 	if(nullptr == Get()->TableInstanceMap[Tablenamekey]->DataTable)
// 	{
// 		GLog->Log(TEXT("TableLoader"), ELogVerbosity::Error, FString::Printf(TEXT("Not Loading %s"), *TableName));
// 		Get()->TableInstanceMap.Remove(Tablenamekey);
// 		return nullptr;
// 	}
//
// 	FName RowName = FName(*FString::FromInt(index));
// 	T* FindTable = Get()->TableInstanceMap[Tablenamekey]->DataTable->FindRow<T>(RowName, FString(""), false);
// 	return FindTable;
// }

// FString UTableLoader::MakeResourcePath(FString filename)
// {
// 	return FString::Printf(TEXT("DataTable'/Game/TableData/%s.%s'"),*filename, *filename);
// }

// UTableLoader* UTableLoader::Get()
// {
// 	if (false == TableLoaderInstance.IsValid())
// 	{
// 		TableLoaderInstance = NewObject<UTableLoader>();
// 		TableLoaderInstance->AddToRoot();
// 	}
// 	if (TableLoaderInstance.IsValid())
// 	{
// 		return TableLoaderInstance.Get();
// 	}
// 	return nullptr;
// }