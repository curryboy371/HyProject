// Fill out your copyright notice in the Description page of Project Settings.


#include "HyDeveloperSettings.h"

const UHyDeveloperSettings* UHyDeveloperSettings::GetDeveloperSetting()
{
	static const UHyDeveloperSettings* Settings = GetDefault<UHyDeveloperSettings>();
	return Settings;
}

UHyDeveloperSettings* UHyDeveloperSettings::GetDeveloperSettingRef()
{
	static UHyDeveloperSettings* Settings = GetMutableDefault<UHyDeveloperSettings>();
	return Settings;
}
