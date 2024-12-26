// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

        AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
        GetBlackboardComponent()->SetValueAsBool(TEXT("IsPatrol"), ControlledCharacter->bIsPatrol);

        if (ControlledCharacter->bIsPatrol)
        {
            GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolStartLocation"), ControlledCharacter->GetActorLocation());

            if (ControlledCharacter->PatrolLocation == FVector::ZeroVector)
            {
                ControlledCharacter->PatrolLocation = ControlledCharacter->GetActorLocation();
            }

            GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolDestination"), ControlledCharacter->PatrolLocation);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AIBehavior is nullptr"));
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;
}

