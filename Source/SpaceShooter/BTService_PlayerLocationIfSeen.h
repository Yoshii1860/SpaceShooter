// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UBTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerLocationIfSeen();

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 25.0f;

	UPROPERTY(EditAnywhere)
	float ViewAngle = 120.0f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TriggeredKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void TriggerOtherAI(UBehaviorTreeComponent& OwnerComp);
};
