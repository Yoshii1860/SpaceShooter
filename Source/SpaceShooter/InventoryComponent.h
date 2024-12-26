// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoItem.h"
#include "InventoryComponent.generated.h"

class AGun;
class AAmmoItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	TArray<TSubclassOf<AGun>> GunClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<AGun*> Guns;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CreateGun(TSubclassOf<AGun> GunClass);

	AGun* GetGun();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SwitchGun(bool bIsScrollingUp);

	void SwitchGunUp();
	void SwitchGunDown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<EAmmoType, int32> AmmoCount;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddAmmo(EAmmoType AmmoType, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetAmmo(EAmmoType AmmoType);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ConsumeAmmo(EAmmoType AmmoType, int32 Amount);

	int32 CurrentWeaponIndex = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
