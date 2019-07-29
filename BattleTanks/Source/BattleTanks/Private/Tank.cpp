// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetTankComponentPart(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTankComponentPart(BarrelToSet, TurretToSet);
	Barrel = BarrelToSet;
}

void ATank::Firing()
{

	if (!Barrel) return;

	const FVector Location = Barrel->GetSocketLocation(FName("Socket_Projectile"));
	const FRotator Rotation = Barrel->GetSocketRotation("Socket_Projectile");
	GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Location, Rotation);
	//UE_LOG(LogTemp, Warning, TEXT("Socket rotation: %s"), *Rotation.ToString());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

