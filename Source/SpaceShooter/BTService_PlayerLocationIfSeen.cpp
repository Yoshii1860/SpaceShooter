// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
    {
        // Check if AI is triggered by bool bIsUnderAttack from the ShooterCharacter
        AShooterCharacter* AICharacter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
        if (AICharacter && AICharacter->bIsUnderAttack)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TriggeredKey.SelectedKeyName, true);
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
            TriggerOtherAI(OwnerComp);
            return;
        }

        // Check if player is in line of sight
        bool bSeen = OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn);
        if (!bSeen)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TriggeredKey.SelectedKeyName, false);
            OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
            return;
        }

        // Check if player is in front of AI
        FVector DirectionToPlayer = PlayerPawn->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
        DirectionToPlayer.Normalize();
        float DotProduct = FVector::DotProduct(OwnerComp.GetAIOwner()->GetPawn()->GetActorForwardVector(), DirectionToPlayer);
        
        // Check if player is in front of AI in a cone of specified angle
        float AngleInRadians = acos(DotProduct);
        float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);
        bool bPlayerInViewAngle = AngleInDegrees <= ViewAngle;

        // Raise the acceptance radius if player is in AI's view angle
        float RadiusToCheck = bPlayerInViewAngle ? AcceptanceRadius * 3 : AcceptanceRadius;

        if (OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(PlayerPawn) <= RadiusToCheck)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TriggeredKey.SelectedKeyName, true);
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
            TriggerOtherAI(OwnerComp);
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(TriggeredKey.SelectedKeyName, false);
            OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
        }
    }
}

void UBTService_PlayerLocationIfSeen::TriggerOtherAI(UBehaviorTreeComponent& OwnerComp)
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterCharacter::StaticClass(), FoundActors);
    for (AActor* Actor : FoundActors)
    {
        AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Actor);
        if (ShooterCharacter && OwnerComp.GetAIOwner()->GetPawn()->GetDistanceTo(ShooterCharacter) <= AcceptanceRadius && !ShooterCharacter->bIsUnderAttack)
        {
            ShooterCharacter->SetTriggered();
        }
    }
}