// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlaySoundWithBoolChange.generated.h"

/**
 * 
 */
class UBlackboardComponent;
class USoundCue;

UCLASS()
class SPACESHOOTER_API UBTTask_PlaySoundWithBoolChange : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PlaySoundWithBoolChange();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundCue* SoundToPlay;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector IsPlayingSoundKey;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
