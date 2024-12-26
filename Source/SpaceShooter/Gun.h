// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoItem.h"
#include "Gun.generated.h"

UCLASS()
class SPACESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	void ProcessShot();

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Sphere;

	UFUNCTION(BlueprintCallable)
		void PickupGun();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* SwitchSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		EAmmoType AmmoType;

	UPROPERTY(EditDefaultsOnly)
		int32 InitialAmmo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
 
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
		USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
		USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
		float FireRate = 0.25f;

	UPROPERTY(EditAnywhere)
		float FireRange = 1000;

	UPROPERTY(EditAnywhere)
		float Damage = 10;

	UPROPERTY(EditAnywhere)
		bool bIsExplosive = false;

	UPROPERTY(EditAnywhere)
		float ExplosionRadius = 300;

	FTimerHandle FireRateTimerHandle;

	bool bCanFire = true;

	void ResetFire();

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* NoAmmoSound;

	class UInventoryComponent* Inventory;

	void Explode(const FHitResult& Hit, const FVector& ShotDirection);

	void DealDamage(const FHitResult& Hit, const FVector& ShotDirection);

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> ExplosionCameraShakeClass;
};
