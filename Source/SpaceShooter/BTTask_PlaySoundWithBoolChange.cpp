// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlaySoundWithBoolChange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTTask_PlaySoundWithBoolChange::UBTTask_PlaySoundWithBoolChange()
{
    NodeName = TEXT("Play Sound For Spotted");
}

EBTNodeResult::Type UBTTask_PlaySoundWithBoolChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        bool IsPlayingSound = BlackboardComp->GetValueAsBool(IsPlayingSoundKey.SelectedKeyName);

        if (!IsPlayingSound)
        {
            BlackboardComp->SetValueAsBool(IsPlayingSoundKey.SelectedKeyName, true);
            UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAttached(SoundToPlay, OwnerComp.GetAIOwner()->GetPawn()->GetRootComponent());
        }
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}