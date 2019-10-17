// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// does not simulate physic, therefore wont break the hierachy
	PhysicConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physic Constraint"));
	SetRootComponent(PhysicConstraint);
	
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(PhysicConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!TankRoot) return;
	PhysicConstraint->SetConstrainedComponents(TankRoot, NAME_None, Wheel, NAME_None);
}