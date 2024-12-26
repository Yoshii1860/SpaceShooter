// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ChangeMoveSpeed.generated.h"

UCLASS()
class SPACESHOOTER_API UBTService_ChangeMoveSpeed : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_ChangeMoveSpeed();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	bool bIsWalking = false;
};
