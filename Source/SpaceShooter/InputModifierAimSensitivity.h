// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "CustomInputUserSettings.h"
#include "InputModifierAimSensitivity.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UInputModifierAimSensitivity : public UInputModifier
{
	GENERATED_BODY()

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
 
	UPROPERTY(Transient)
	UCustomInputUserSettings* Settings;
	
};
