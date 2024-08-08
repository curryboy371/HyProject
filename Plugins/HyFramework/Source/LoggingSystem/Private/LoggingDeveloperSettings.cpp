// Fill out your copyright notice in the Description page of Project Settings.


#include "LoggingDeveloperSettings.h"

const ULoggingDeveloperSettings* ULoggingDeveloperSettings::GetDeveloperSetting()
{

	static const ULoggingDeveloperSettings* Settings = GetDefault<ULoggingDeveloperSettings>();

	return Settings;
}

ULoggingDeveloperSettings* ULoggingDeveloperSettings::GetDeveloperSettingRef()
{
	static ULoggingDeveloperSettings* Settings = GetMutableDefault<ULoggingDeveloperSettings>();

	return Settings;
}
