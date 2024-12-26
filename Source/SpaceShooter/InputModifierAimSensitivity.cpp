// Fill out your copyright notice in the Description page of Project Settings.


#include "InputModifierAimSensitivity.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

FInputActionValue UInputModifierAimSensitivity::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	if(!Settings)
	{
		Settings = PlayerInput->GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UCustomInputUserSettings>();
	}
	
	return CurrentValue.Get<FVector>() * Settings->GetAimSensitivityVector();
}