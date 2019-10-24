// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:	
	
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	USphereComponent* Axle = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalMagnitudeThisFrame = 0;

	void SetupConstraint();

	void ApplyForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
