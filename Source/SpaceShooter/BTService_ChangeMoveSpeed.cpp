// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeMoveSpeed.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeMoveSpeed::UBTService_ChangeMoveSpeed()
{
    NodeName = TEXT("Change Move Speed");
}

void UBTService_ChangeMoveSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {
        if (AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(AIController->GetPawn()))
        {
            ControlledCharacter->SetMovementSpeed(bIsWalking);
        }
    }
}
