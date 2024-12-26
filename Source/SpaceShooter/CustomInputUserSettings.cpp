// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomInputUserSettings.h"

void UCustomInputUserSettings::SetAimSensitivity(float SensitivityX, float SensitivityY)
{
	AimSensitivityX = SensitivityX;
	AimSensitivityY = SensitivityY;
 
	// this does nothing by default except trigger a delegate to bind to in order to update UIs
	ApplySettings();
}
 
FVector UCustomInputUserSettings::GetAimSensitivityVector() const
{
	// convenience function to use in input modifier
	return FVector(AimSensitivityX, AimSensitivityY, 1);
}