// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShooterGameMode.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AKillEmAllGameMode : public ASpaceShooterGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PauseGame();

private:
	void EndGame(bool bIsPlayerWinner);
};
