// Fill out your copyright notice in the Description page of Project Settings.


#include "HyCoreDeveloperSettings.h"

const UHyCoreDeveloperSettings* UHyCoreDeveloperSettings::GetDeveloperSetting()
{

	static const UHyCoreDeveloperSettings* Settings = GetDefault<UHyCoreDeveloperSettings>();

	return Settings;
}

UHyCoreDeveloperSettings* UHyCoreDeveloperSettings::GetDeveloperSettingRef()
{
	static UHyCoreDeveloperSettings* Settings = GetMutableDefault<UHyCoreDeveloperSettings>();

	return Settings;
}
