// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetControlledTank() && !GetPlayerTank()) return;

	FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(PlayerLocation);
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
