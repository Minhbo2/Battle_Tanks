// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:

	UTankTrack();

	/**
	Tank mass = 40,000kg
	Force = mass * acceleration
	10ms-2 (1g) acceleration* 
	400000 Newtons in driving force */
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxForce = 400000;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
};
