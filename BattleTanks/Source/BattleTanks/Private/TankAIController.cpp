// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank     = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (ensure(ControlledTank && PlayerTank)) 
	{
		auto AimingComponentRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		FVector PlayerLocation  = PlayerTank->GetActorLocation();
		AimingComponentRef->AimAt(PlayerLocation);
		MoveToActor(PlayerTank, AcceptanceRadius);

		if(AimingComponentRef->GetFiringState() == EFiringStatus::Locked)
			AimingComponentRef->Firing();
	}

}