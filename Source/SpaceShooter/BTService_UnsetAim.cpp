// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UnsetAim.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_UnsetAim::UBTService_UnsetAim()
{
    NodeName = TEXT("Unset Aim");
}

void UBTService_UnsetAim::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* Character = OwnerComp.GetAIOwner()->GetPawn();
    
    // Cast to ShooterCharacter
    if (AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Character))
    {
        // Set Aim Bool
        ShooterCharacter->SetAiming(false);
    }
}
