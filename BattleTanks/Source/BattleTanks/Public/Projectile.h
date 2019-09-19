// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float LaunchSpeed);

private:

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UStaticMeshComponent * CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = Component) 
	UParticleSystemComponent * LaunchBlast;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UParticleSystemComponent * ImpactBlast;

	UPROPERTY(VisibleAnywhere, Category = Component)
	URadialForceComponent* ImpulseForce;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float ProjectileDamage;

	/*UPROPERTY(VisibleAnywhere, Category = Setup)
	float DestroyDelay;*/

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};

