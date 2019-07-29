// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetilePool.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
AProjetilePool::AProjetilePool()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

int32 AProjetilePool::GetCurrentPoolAmount()
{
	return Pool.Num();
}

AProjectile * AProjetilePool::CheckOutProjectile()
{
	if (GetCurrentPoolAmount() < 1) return nullptr;
	return Pool.Pop();
}

void AProjetilePool::ReturnProjectileToPool(AProjectile * Projectile)
{
	Pool.Push(Projectile);
}

// Called when the game starts or when spawned
void AProjetilePool::BeginPlay()
{
    Super::BeginPlay();
    
	if (!Projectile) return;

	SpawnProjectiles(MaxPoolAmount);

	UE_LOG(LogTemp, Warning, TEXT("Pool Amount: %d"), GetCurrentPoolAmount());
}

void AProjetilePool::SpawnProjectiles(int32 PoolAmount)
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