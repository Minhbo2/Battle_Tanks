// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
AProjectilePool::AProjectilePool()
{

}

int32 AProjectilePool::GetCurrentPoolAmount()
{
	return Pool.Num();
}

AProjectile * AProjectilePool::CheckOutProjectile()
{
	if (GetCurrentPoolAmount() < 1) return nullptr; //OPTIONAL: expand pool size if no projectile is available
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
	if (!Projectile) return;

	SpawnProjectiles(MaxPoolAmount);
}

void AProjectilePool::SpawnProjectiles(int32 PoolAmount)
{
	for (auto i = 0; i < MaxPoolAmount; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			FVector(0),
			FRotator(0),
			SpawnParams);

		if (!NewProjectile) break;
		Pool.Add(NewProjectile);
	}
}
