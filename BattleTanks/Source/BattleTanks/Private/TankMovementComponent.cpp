// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

UTankMovementComponent::UTankMovementComponent()
{
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRightTurn(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendLeftTurn(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;

	LeftTrack  = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// get normal vector/unit vector of velocity w/o altering the MoveVelocity
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	// https://www.udemy.com/unreal-engine-c-developer-archived-course/learn/lecture/13957200#questions
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForwardDirection);

	IntendMoveForward(ForwardThrow);
}
