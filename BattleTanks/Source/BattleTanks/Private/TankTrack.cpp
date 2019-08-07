// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "UObject/ConstructorHelpers.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UTankTrack::UTankTrack()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> TrackStaticMesh(TEXT("/Game/Tank_StaticMesh/tank_fbx_Track"));
	ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysMaterial(TEXT("/Game/Material/Track"));
	if (TrackStaticMesh.Object || PhysMaterial.Object)
	{
		SetStaticMesh(TrackStaticMesh.Object);
		SetRelativeLocation(FVector(0));

		//SetPhysMaterialOverride(PhysMaterial.Object);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	// incase player has access to throttle value
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);

	/**
	Calculate force and locations to apply the force to.
	*/
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	// Cast To primitive component since scene component does not have AddForceAtLocation method
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
