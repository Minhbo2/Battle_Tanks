// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "UObject/ConstructorHelpers.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "SprungWheel.h"
#include "WheelSpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UStaticMesh> TrackStaticMesh(TEXT("/Game/Tank_StaticMesh/tank_fbx_Track"));
	ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Game/Material/Track"));
	if (TrackStaticMesh.Object || PhysMaterial.Object)
	{
		SetStaticMesh(TrackStaticMesh.Object);
		SetRelativeLocation(FVector(0));

		//SetPhysMaterialOverride(PhysMaterial.Object);
	}

	// making sure Collison -> Simulation Generates Hit Event check box is always checked
	SetNotifyRigidBodyCollision(true);
}


// TODO: Refactor to have this run once
TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<UWheelSpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor * SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

void UTankTrack::SetThrottle(float Throttle)
{
	// incase player has access to throttle value
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

// LEGACY; using WheelConstraint instead.
void UTankTrack::ApplySidewaysForce()
{
	// calculate sideway/slippage speed of the track
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// getting the required acceleration this frame to apply
	auto CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetTimeSeconds() * GetRightVector();
	// getting force to apply as friction (F = m x a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Divide by 2 since there are 2 tracks.
	TankRoot->AddForce(CorrectionForce);
}