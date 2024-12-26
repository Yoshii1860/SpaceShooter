// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Gun.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KillEmAllGameMode.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create Inventory Component
	Inventory = NewObject<UInventoryComponent>(this, TEXT("Inventory"));	
	if (Inventory != nullptr)
	{
		Inventory->CreateGun(GunClass);
		CurrentGun = Inventory->GetGun();
		Inventory->SwitchGunUp();
	}

	GameMode = Cast<AKillEmAllGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode not found in PlayerCharacter"));
	}

	if (CurrentGun != nullptr)
	{
		// Rebound actions after spawning gun
		SetupPlayerInputComponent(GetWorld()->GetFirstPlayerController()->InputComponent);
	}
}

void APlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
		//Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SetAiming, true);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerCharacter::SetAiming, false);
		// Firing
		if (CurrentGun != nullptr)
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);
		}
		// Switching Weapons
		EnhancedInputComponent->BindAction(SwitchGunUpAction, ETriggerEvent::Completed, Inventory, &UInventoryComponent::SwitchGunUp);
		EnhancedInputComponent->BindAction(SwitchGunDownAction, ETriggerEvent::Completed, Inventory, &UInventoryComponent::SwitchGunDown);
		// Pause Game
		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, GameMode, &AKillEmAllGameMode::PauseGame);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

bool APlayerCharacter::Heal(float HealAmount)
{
	if (Health >= MaxHealth)
	{
		return false;
	}

	Health += HealAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	return true;
}


