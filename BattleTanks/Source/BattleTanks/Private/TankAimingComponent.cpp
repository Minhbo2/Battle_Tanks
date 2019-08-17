// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "EngineUtils.h"
#include "ProjectilePool.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateProjectilePool();

	LastTimeFired = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastTimeFired) < ReloadTimeInSeconds)
		FiringStatus = EFiringStatus::Reloading;
	else if(IsBarrelMoving())
		FiringStatus = EFiringStatus::Aiming;
	else
		FiringStatus = EFiringStatus::Locked;
}

void UTankAimingComponent::SetTankComponentPart(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel && !Turret) return;

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Socket_Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, // world context object of where this method is originate from
		OutLaunchVelocity, // reference to a FVector LaunchVelocity as a Out parameter
		StartLocation, // start location
		HitLocation, // end location, where the HitLocation projected Ray hit
		LaunchSpeed, // speed of which to launch the projectile
		false, // using high arch
		0, // collision radius 
		0, // override gravity
		ESuggestProjVelocityTraceOption::DoNotTrace // tracing option
	);

	// Calculate launch velocity
	if(bHaveAimSolution)
	{
		this->AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(this->AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// calculate the difference between current barrel rotation and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); // -1 is max downward movement, +1 max upward movement

	if(FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->Rotate(DeltaRotator.Yaw);
	else
		Turret->Rotate(-DeltaRotator.Yaw);
}

void UTankAimingComponent::Firing()
{
	if (!ensure(Barrel || ProjectilePool)) return;

	if (FiringStatus != EFiringStatus::Reloading)
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
}

void UTankAimingComponent::CreateProjectilePool()
{
	ProjectilePool = GetWorld()->SpawnActor<AProjectilePool>(ProjectilePoolBP, FVector(0), FRotator(0));
}

bool UTankAimingComponent::IsBarrelMoving()
{
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}
