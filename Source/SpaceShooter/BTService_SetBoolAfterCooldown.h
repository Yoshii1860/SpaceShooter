// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetBoolAfterCooldown.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UBTService_SetBoolAfterCooldown : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_SetBoolAfterCooldown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float CooldownTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	bool bSetBoolTo = true;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float TimeSinceLastSet = 0.0f;



};
