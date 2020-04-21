// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Subscribe to OnDeath delegate only when we for sure to have a possessed tank
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) return;

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SearchAndDestroy();
}

void ATankAIController::SearchAndDestroy()
{
	// TODO: can store both into global vars instead of local/run every frame
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (ensure(ControlledTank && PlayerTank))
	{
		auto AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		FVector PlayerLocation = PlayerTank->GetActorLocation();
		AimingComponentRef->AimAt(PlayerLocation);
		MoveToActor(PlayerTank, AcceptanceRadius);

		if (AimingComponentRef->GetFiringState() == EFiringStatus::Locked)
			AimingComponentRef->Firing();
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) return;

	GetPawn()->DetachFromControllerPendingDestroy();
}