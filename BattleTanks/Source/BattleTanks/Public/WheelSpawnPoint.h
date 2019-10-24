// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WheelSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UWheelSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheelSpawnPoint();

	AActor* GetSpawnedActor() const { return SpawnedActor; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY()
	AActor* SpawnedActor;
};
