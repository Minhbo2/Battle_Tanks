// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectilePool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankComponentPart(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Firing();

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetCurrentAmmoCount() const { return CurrentAmmoCount; }

	EFiringStatus GetFiringState() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:	

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	float LastTimeFired = 0.0f;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 MaxAmmoCount = 2;

	int32 CurrentAmmoCount;

	// specify in tank BP, selecting aiming comp
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectilePool> ProjectilePoolBP;

	AProjectilePool * ProjectilePool;

	UTankBarrel * Barrel = nullptr;
	
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void CreateProjectilePool();

	bool IsBarrelMoving();
};
