// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "CustomInputUserSettings.generated.h"

UCLASS()
class SPACESHOOTER_API UCustomInputUserSettings : public UEnhancedInputUserSettings
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetAimSensitivity(float SensitivityX, float SensitivityY);
 
	UFUNCTION(BlueprintCallable)
	FVector GetAimSensitivityVector() const;
	
protected:
	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityX = 1;
	
	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityY = 1;

};
