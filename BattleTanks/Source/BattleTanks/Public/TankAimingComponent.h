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
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankComponentPart(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:	

	UTankBarrel * Barrel = nullptr;
	
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
