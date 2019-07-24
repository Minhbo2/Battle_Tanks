// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankBarrel();

	// -1 is max downward movement, +1 max upward movement
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreePerSecond = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevation = 30.0f; // Pitch

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevation = 0.0f; // Pitch
};
