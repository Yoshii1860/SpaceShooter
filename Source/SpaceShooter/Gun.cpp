// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	// Create sphere collider on blueprint
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter != nullptr)
	{
		Inventory = PlayerCharacter->Inventory;
	}
}

void AGun::PickupGun()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->Inventory->CreateGun(GunClass);
		PlayerCharacter->Inventory->SwitchGunUp();
		Destroy();
	}
}

void AGun::PullTrigger()
{
	if (!bCanFire)
		return;
	
	bCanFire = false;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AGun::ResetFire, FireRate);

	if (!Inventory->ConsumeAmmo(AmmoType, 1))
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }

	ProcessShot();
}

void AGun::ProcessShot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		float DistanceToImpact = (Hit.Location - GetActorLocation()).Size();
		float VolumeMultiplier = 1.0f - DistanceToImpact / FireRange;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location, VolumeMultiplier);

		if (bIsExplosive)
		{
			Explode(Hit, ShotDirection);
		}
		else
		{
			DealDamage(Hit, ShotDirection);
		}
	}
}

void AGun::Explode(const FHitResult& Hit, const FVector& ShotDirection)
{
	// Create a sphere or cylinder collision volume
	FCollisionShape Shape;
	Shape.SetSphere(ExplosionRadius);

	// Find overlapping actors
	TArray<FHitResult> OutHits;
	GetWorld()->SweepMultiByChannel(OutHits, Hit.Location, Hit.Location, FQuat::Identity, ECC_GameTraceChannel1, Shape);

	// Draw a debug sphere to visualize the explosion radius
	// DrawDebugSphere(GetWorld(), Hit.Location, ExplosionRadius, 12, FColor::Red, false, 5.0f);

	TArray<AActor*> DamagedActors;

	// Damage overlapping actors
	for (const FHitResult& HitResult : OutHits)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && !DamagedActors.Contains(HitActor))
		{
			// Calculate damage based on distance from the explosion
			float Distance = (HitActor->GetActorLocation() - Hit.Location).Size();
			float DamageMultiplier = 1.0f - FMath::Clamp(Distance / ExplosionRadius, 0.0f, 1.0f);
			float DamageToApply = Damage * DamageMultiplier;

			// Apply damage to the hit actor, potentially with reduced damage
			FPointDamageEvent DamageEvent(DamageToApply, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(DamageToApply, DamageEvent, GetOwnerController(), this);

			// Add the hit actor to the list of damaged actors
			DamagedActors.AddUnique(HitActor);
		}
	}

	if (ExplosionCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExplosionCameraShakeClass);
	}
}

void AGun::DealDamage(const FHitResult& Hit, const FVector& ShotDirection)
{
	AActor* HitActor = Hit.GetActor();
	if (HitActor != nullptr)
	{
		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		AController* OwnerController = GetOwnerController();
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	// Get ViewPoint
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	ShotDirection = -ViewPointRotation.Vector();
	FVector End = ViewPointLocation + ViewPointRotation.Vector() * FireRange;

	// Ignore self
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, ViewPointLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) 
		return nullptr;
	return OwnerPawn->GetController();
}

void AGun::ResetFire()
{
	bCanFire = true;
}


