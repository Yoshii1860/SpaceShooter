// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SpaceShooterGameMode.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// if not possessed by player
	if (!IsPlayerControlled())
	{
		FirstGun = GetWorld()->SpawnActor<AGun>(GunClass);
		FirstGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		FirstGun->SetOwner(this);

		CurrentGun = FirstGun;
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacter::ResetTriggered()
{
	bIsUnderAttack = false;
}

void AShooterCharacter::SetTriggered()
{
	bIsUnderAttack = true;
	GetWorldTimerManager().SetTimer(TimerHandle_ResetUnderAttack, this, &AShooterCharacter::ResetTriggered, 2.0f);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	bIsUnderAttack = true;
	GetWorldTimerManager().SetTimer(TimerHandle_ResetUnderAttack, this, &AShooterCharacter::ResetTriggered, 2.0f);

	// Call parent implementation
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Update Health
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	// Check if dead
	if (IsDead())
	{
		UAudioComponent* CharacterAudioComponent = FindComponentByClass<UAudioComponent>();
		if (CharacterAudioComponent)
		{
			CharacterAudioComponent->Stop();
		}
		
		if (ASpaceShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASpaceShooterGameMode>())
		{
			GameMode->PawnKilled(this);
		}

		// Detach Controller
		DetachFromControllerPendingDestroy();

		// Disable Collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		return DamageToApply;
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

void AShooterCharacter::Shoot()
{
	if (CurrentGun != nullptr 
	&& IsAiming() && !IsDead())
	{
		CurrentGun->PullTrigger();
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

bool AShooterCharacter::IsAiming() const
{
	return bIsAiming;
}

void AShooterCharacter::SetAiming(bool bAiming)
{
	bIsAiming = bAiming;
}


void AShooterCharacter::SetMovementSpeed(bool bIsWalking)
{
	if (bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}