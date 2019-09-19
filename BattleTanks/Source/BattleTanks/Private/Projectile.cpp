// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	CollisionMesh->bVisible = false;
	CollisionMesh->SetNotifyRigidBodyCollision(false);
	SetRootComponent(CollisionMesh);

	LaunchBlast   = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LaunchBlast->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ImpulseForce = CreateDefaultSubobject<URadialForceComponent>(FName("Impulse Force"));
	ImpulseForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComponent->Activate();
	LaunchBlast->Activate();
	CollisionMesh->SetVisibility(true);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetCollisionProfileName(FName("BlockAllDynamic"));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	CollisionMesh->SetNotifyRigidBodyCollision(false);
	CollisionMesh->SetCollisionProfileName(FName("NoCollision"));
	CollisionMesh->SetVisibility(false);
	ProjectileMovementComponent->Deactivate();
	ImpulseForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ImpulseForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>(), // damage all actors
		this
		);

	// using timer, remember to create a method for OnTimerExpire
	//FTimerHandle Timer; // just a place holder
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}