// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SoundMixModifier.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API USoundMixModifier : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundMix")
		float Volume;

	UFUNCTION(BlueprintCallable)
		static void SetVolume(class USoundClass* SoundClass, class USoundMix* SoundMix, float NewVolume);	
};


