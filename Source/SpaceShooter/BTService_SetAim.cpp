// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetAim.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_SetAim::UBTService_SetAim()
{
    NodeName = TEXT("Set Aim");
}

void UBTService_SetAim::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* Character = OwnerComp.GetAIOwner()->GetPawn();
    
    // Cast to ShooterCharacter
    if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Character))
    {
        // Set Aim Bool
        ShooterCharacter->SetAiming(true);
    }
}