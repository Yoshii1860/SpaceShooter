// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Gun.h"
#include "AmmoItem.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::CreateGun(TSubclassOf<AGun> GunClass)
{
	// Spawn new gun
	AGun* NewGun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (NewGun != nullptr)
	{
		Guns.Add(NewGun);
	}

	// Remove Sphere collider
	NewGun->Sphere->DestroyComponent();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	NewGun->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	NewGun->SetOwner(PlayerCharacter);
    // Hide and disable collision for secondary gun
    NewGun->SetActorHiddenInGame(true);
    NewGun->SetActorEnableCollision(false);

	AddAmmo(NewGun->AmmoType, NewGun->InitialAmmo);
}

void UInventoryComponent::SwitchGunUp()
{
	SwitchGun(true);
}

void UInventoryComponent::SwitchGunDown()
{
	SwitchGun(false);
}

void UInventoryComponent::SwitchGun(bool bIsScrollingUp)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter != nullptr && !PlayerCharacter->IsDead())
	{
		// Hide and disable collision for current gun
		if (PlayerCharacter->CurrentGun != nullptr)
		{
			PlayerCharacter->CurrentGun->SetActorHiddenInGame(true);
			PlayerCharacter->CurrentGun->SetActorEnableCollision(false);
		}

		// Increment or decrement weapon index
		if (bIsScrollingUp)
		{
			CurrentWeaponIndex = (CurrentWeaponIndex - 1 + Guns.Num()) % Guns.Num();
		}
		else
		{
			CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Guns.Num();
		}

		// Show and enable collision for new gun
		PlayerCharacter->CurrentGun = Guns[CurrentWeaponIndex];
		PlayerCharacter->CurrentGun->SetActorHiddenInGame(false);
		PlayerCharacter->CurrentGun->SetActorEnableCollision(true);

		if (Guns.Num() > 1)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlayerCharacter->CurrentGun->SwitchSound, PlayerCharacter->GetActorLocation());
		}
	}
}

AGun* UInventoryComponent::GetGun()
{
	return Guns[CurrentWeaponIndex];
}

void UInventoryComponent::AddAmmo(EAmmoType AmmoType, int32 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Ammo: %d"), Amount);

	if (AmmoCount.Contains(AmmoType))
	{
		AmmoCount[AmmoType] += Amount;
	}
	else
	{
		AmmoCount.Add(AmmoType, Amount);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Ammo Count: %d"), AmmoCount[AmmoType]);
}

int32 UInventoryComponent::GetAmmo(EAmmoType AmmoType)
{
	if (AmmoCount.Contains(AmmoType))
	{
		return AmmoCount[AmmoType];
	}

	return 0;
}

bool UInventoryComponent::ConsumeAmmo(EAmmoType AmmoType, int32 Amount)
{
	if (AmmoCount.Contains(AmmoType))
	{
		if (AmmoCount[AmmoType] >= Amount)
		{
			AmmoCount[AmmoType] -= Amount;
			return true;
		}
	}

	return false;
}



