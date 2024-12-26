// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);

	bool bPlayerDead = false;
	
};
