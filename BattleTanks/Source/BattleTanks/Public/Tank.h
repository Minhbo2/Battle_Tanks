// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class AProjectilePool;
class UTankTrack;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankComponentPart(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Firing();

protected:

	UTankAimingComponent * TankAimingComponent = nullptr;

private:	

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	float LastTimeFired = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectilePool> ProjectilePoolBP;

	AProjectilePool * ProjectilePool;

	// local barrel ref for spawning
	UTankBarrel* Barrel = nullptr;

	UTankTrack* LeftTrack;

	UTankTrack* RightTrack;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void CreateProjectilePool();
};
