// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetAim.generated.h"

/**
 * 
 */


UCLASS()
class SPACESHOOTER_API UBTService_SetAim : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SetAim();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
