// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"

void ASpaceShooterGameMode::PawnKilled(APawn* PawnKilled)
{
    if (PawnKilled == UGameplayStatics::GetPlayerPawn(this, 0))
    {
        bPlayerDead = true;
    }

}
