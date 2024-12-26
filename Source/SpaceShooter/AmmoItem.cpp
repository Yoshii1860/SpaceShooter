// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAmmoItem::AAmmoItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void AAmmoItem::BeginPlay()
{
	Super::BeginPlay();
	
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAmmoItem::OnOverlapBegin);
}

void AAmmoItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is the player
	if (OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			PlayerCharacter->Inventory->AddAmmo(AmmoType, AmmoCount);
            if (PickupSound)
            {
                UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
            }
            Destroy();
        }
    }
}
