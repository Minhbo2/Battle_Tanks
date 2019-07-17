// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* ControlledTank = GetControlledTank();

	if (ControlledTank)
		UE_LOG(LogTemp, Warning, TEXT("Possess: %s"), *ControlledTank->GetName());

	APawn* PlayerTank = GetPlayerTank();
	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *PlayerTank->GetName());
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = Cast<AController>(GetWorld()->GetFirstPlayerController())->GetPawn();
	return Cast<ATank>(PlayerTank);
}
