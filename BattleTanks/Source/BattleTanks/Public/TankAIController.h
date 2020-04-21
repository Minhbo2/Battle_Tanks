// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

protected: 
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float AcceptanceRadius = 3000;


private:

	void Tick(float DeltaTime) override;

	void SearchAndDestroy();
	
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossedTankDeath();
};
