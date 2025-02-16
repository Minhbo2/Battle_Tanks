// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent * AimCompRef);

private:


	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	UTankAimingComponent * AimingComponentRef;

	void AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector & OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const ;

	UFUNCTION()
	void OnPossedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;
};
