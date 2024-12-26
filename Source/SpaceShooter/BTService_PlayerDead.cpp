// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDead.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerDead::UBTService_PlayerDead()
{
    NodeName = TEXT("Player Dead");
}

void UBTService_PlayerDead::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Get SpaceShooterGameMode and check if player is dead
    ASpaceShooterGameMode* SpaceShooterGame = Cast<ASpaceShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    if (SpaceShooterGame->bPlayerDead)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
    }
}
