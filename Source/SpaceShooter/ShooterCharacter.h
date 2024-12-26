// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SPACESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	float Health = 100;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	bool IsAiming() const;

    void SetAiming(bool bAiming);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	UPROPERTY(BlueprintReadOnly)
	AGun* CurrentGun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* FirstGun;

	bool bIsUnderAttack = false;

	void SetTriggered();

	UPROPERTY(EditAnywhere)
	bool bIsPatrol = false;

	UPROPERTY(EditAnywhere)
	FVector PatrolLocation;

	void SetMovementSpeed(bool bIsWalking);

private:

	UPROPERTY(EditAnywhere)
	float FireRate = 0.4f;

	bool bIsAiming = false;

	void ResetTriggered();

	FTimerHandle TimerHandle_ResetUnderAttack;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 110.0f;

	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 400.0f;
};
