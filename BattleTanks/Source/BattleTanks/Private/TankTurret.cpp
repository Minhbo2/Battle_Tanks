// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Engine/StaticMesh.h"
#include "ConstructorHelpers.h"

UTankTurret::UTankTurret()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> TankTurret(TEXT("/Game/Tank_StaticMesh/tank_fbx_Turret"));

	if (!TankTurret.Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("No reference found to tank turret"));
		return;
	}
	this->SetStaticMesh(TankTurret.Object);
	this->SetRelativeLocation(FVector(0));
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * DegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
