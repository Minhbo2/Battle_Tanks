// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "EngineUtils.h"
#include "ProjectilePool.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetTankComponentPart(UTankBarrel * BarrelToSet, UTankAimingComponent * AimingComponent)
{
	if (!BarrelToSet || !AimingComponent) return;

	TankAimingComponent = AimingComponent;
	Barrel              = BarrelToSet;
}

void ATank::Firing()
{
	bool bReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeInSeconds;

	if (Barrel && ProjectilePool && bReloaded)
	{
		const FVector Location  = Barrel->GetSocketLocation(FName("Socket_Projectile"));
		const FRotator Rotation = Barrel->GetSocketRotation("Socket_Projectile");
		auto Projectile         = ProjectilePool->CheckOutProjectile();

		if (Projectile)
		{
			Projectile->SetActorLocation(Location);
			Projectile->SetActorRotation(Rotation);
			Projectile->LaunchProjectile(LaunchSpeed);
			LastTimeFired = FPlatformTime::Seconds();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Socket rotation: %s"), *Rotation.ToString());
}

void ATank::CreateProjectilePool()
{
	ProjectilePool = GetWorld()->SpawnActor<AProjectilePool>(ProjectilePoolBP, FVector(0), FRotator(0));
}