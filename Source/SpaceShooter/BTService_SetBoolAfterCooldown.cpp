// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetBoolAfterCooldown.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetBoolAfterCooldown::UBTService_SetBoolAfterCooldown()
{
    NodeName = TEXT("Set Bool After Cooldown");
}

void UBTService_SetBoolAfterCooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    bool bValue = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());

    if (bValue == bSetBoolTo)
        return;

    TimeSinceLastSet += DeltaSeconds;

    if (TimeSinceLastSet >= CooldownTime)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bSetBoolTo);
        TimeSinceLastSet = 0.0f;
    }
}