// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Engine/StaticMesh.h"
#include "ConstructorHelpers.h"
#include "Engine/World.h"


UTankBarrel::UTankBarrel()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> TankBarrel (TEXT("/Game/Tank_StaticMesh/tank_fbx_Barrel"));

	if (!TankBarrel.Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("No reference found to tank barrel"));
		return;
	}
	this->SetStaticMesh(TankBarrel.Object);
	this->SetRelativeLocation(FVector(0));
}

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}