// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set tick to run after Physics
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	// does not simulate physic, therefore wont break the hierachy
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physic Constraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(TEXT("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);
	
	Wheel = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
		TotalMagnitudeThisFrame = 0; // reset force for the next frame
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!TankRoot) return;
	MassWheelConstraint->SetConstrainedComponents(TankRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalMagnitudeThisFrame);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}
