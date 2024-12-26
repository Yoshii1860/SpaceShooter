// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "Gun.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Get AI Controller
    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {
        // Get Pawn
        if (AShooterCharacter* Character = Cast<AShooterCharacter>(AIController->GetPawn()))
        {
            Character->CurrentGun->ProcessShot();
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
