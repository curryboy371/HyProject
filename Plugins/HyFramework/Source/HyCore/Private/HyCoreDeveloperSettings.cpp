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

const bool UHyCoreDeveloperSettings::IsDrawEnable() const
{
	if(DebugDrawOption != EDebugDrawOption::EDrawOption_None)
	{
		return true;
	}

	return false;
}

const bool UHyCoreDeveloperSettings::IsDebugDrawMovement() const
{
	if (IsDrawEnable())
	{
		if (DebugDrawOption == EDebugDrawOption::EDrawOption_All)
		{
			return true;
		}
		else
		{
			return DebugDrawSelectTypes.Contains(EDebugDrawType::EDrawType_Movement);
		}
	}

	return false;
}

const bool UHyCoreDeveloperSettings::IsDebugDrawCollision() const
{
	if (IsDrawEnable())
	{
		if (DebugDrawOption == EDebugDrawOption::EDrawOption_All)
		{
			return true;
		}
		else
		{
			return DebugDrawSelectTypes.Contains(EDebugDrawType::EDrawType_Collision);
		}
	}

	return false;
}

const bool UHyCoreDeveloperSettings::IsDebugDrawWidget() const
{
	if (IsDrawEnable())
	{
		if (DebugDrawOption == EDebugDrawOption::EDrawOption_All)
		{
			return true;
		}
		else
		{
			return DebugDrawSelectTypes.Contains(EDebugDrawType::EDrawType_Widget);
		}
	}

	return false;
}
