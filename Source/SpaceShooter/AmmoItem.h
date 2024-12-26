// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AmmoItem.generated.h"

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	Bullets UMETA(DisplayName = "Bullets"),
	Rockets UMETA(DisplayName = "Rockets")
};

UCLASS()
class SPACESHOOTER_API AAmmoItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAmmoItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    EAmmoType AmmoType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
    int32 AmmoCount = 10;

	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds", meta = (DisplayName = "Pickup Sound"))
	USoundBase* PickupSound;
};