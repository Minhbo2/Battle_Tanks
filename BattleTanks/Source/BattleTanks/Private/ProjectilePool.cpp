// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
AProjectilePool::AProjectilePool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

int32 AProjectilePool::GetCurrentPoolAmount()
{
	return Pool.Num();
}

AProjectile * AProjectilePool::CheckOutProjectile()
{
	if (GetCurrentPoolAmount() < 1) return nullptr; //TODO: expand pool if no projectile is available
	auto Projectile = Pool.Pop();
	return Projectile;
}

void AProjectilePool::ReturnProjectileToPool(AProjectile * Projectile)
{
	Pool.Push(Projectile);
}

// Called when the game starts or when spawned
void AProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	if (!Projectile) return;

	SpawnProjectiles(MaxPoolAmount);
}

void AProjectilePool::SpawnProjectiles(int32 PoolAmount)
{
	for (auto i = 0; i < MaxPoolAmount; i++)
	{
		const FVector Location = GetActorLocation();
		const FRotator Rotation = FRotator(0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			Location,
			Rotation,
			SpawnParams);

		if (!NewProjectile) break;
		Pool.Add(NewProjectile);
	}
}
