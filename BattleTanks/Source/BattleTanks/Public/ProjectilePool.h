// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

class AProjectile;

UCLASS()
class BATTLETANKS_API AProjectilePool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectilePool();

	UFUNCTION(BlueprintCallable, Category = ProjectilePooling)
		int32 GetCurrentPoolAmount();

	UFUNCTION(BlueprintCallable, Category = ProjectilePooling)
		AProjectile * CheckOutProjectile();

	UFUNCTION(BlueprintCallable, Category = ProjectilePooling)
		void ReturnProjectileToPool(AProjectile * Projectile);

private:


	UPROPERTY(EditAnywhere, Category = Setup)
	int32 MaxPoolAmount = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile;

	TArray<AProjectile*> Pool;

	virtual void BeginPlay() override;

	void SpawnProjectiles(int32 PoolAmount);
};