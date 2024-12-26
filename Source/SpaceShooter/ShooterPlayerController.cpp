// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Create HUD Widget
    HUD = CreateWidget(this, HUDClass);

    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();

    if (bIsWinner)
    {
        // Create WinScreen Widget
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        // Create LoseScreen Widget
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    // Restart Level
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}