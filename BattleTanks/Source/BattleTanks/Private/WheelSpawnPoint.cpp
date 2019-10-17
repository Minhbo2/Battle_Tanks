// Fill out your copyright notice in the Description page of Project Settings.


#include "WheelSpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UWheelSpawnPoint::UWheelSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	ConstructorHelpers::FClassFinder<AActor> SprungWheel(TEXT("/Game/Blueprint/SprungWheel_BP"));
	if(SprungWheel.Succeeded())
		SpawnClass = SprungWheel.Class;
}


// Called when the game starts
void UWheelSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// SpawnActorDeferred prevent Construction script and BeginPlay from running
	// SpawnClass, i.e SprungWheel trying to get its parent before the attachment process begins
	// therefore, it will return null. This justify the use of SpawnActorDeffered.
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (!NewActor) return;
	// using KeepWorldTransform since the SpawnActor is spawned in the desired location already
	NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void UWheelSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

