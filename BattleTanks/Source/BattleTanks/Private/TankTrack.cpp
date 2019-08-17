// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "UObject/ConstructorHelpers.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

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

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// incase player has access to throttle value
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(Throttle);
}

void UTankTrack::DriveTrack(float Throttle)
{
	/**
	Calculate force and locations to apply the force to.
	*/
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	// Cast To primitive component since scene component does not have AddForceAtLocation method
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

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