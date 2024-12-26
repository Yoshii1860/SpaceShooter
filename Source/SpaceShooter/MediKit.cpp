// Fill out your copyright notice in the Description page of Project Settings.


#include "MediKit.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMediKit::AMediKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void AMediKit::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMediKit::OnOverlapBegin);
}

// Called every frame
void AMediKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMediKit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is the player
	if (OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			bool bCanHeal = PlayerCharacter->Heal(HealAmount);
			if (bCanHeal)
			{
				if (PickupSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
				}

				Destroy();
			}
        }
    }
}
