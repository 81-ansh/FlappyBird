// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.h"
#include "PipeSpawner.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APipeSpawner();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APipeActor> PipeSpawnClass;
	
	UPROPERTY(EditAnywhere)
	float SpawnInterval = 100.f;
	
	UPROPERTY(EditAnywhere)
	float ZOffsetMin = 100.f;
	
	UPROPERTY(EditAnywhere)
	float ZOffsetMax = 300.f;
	
	FTimerHandle SpawnTimer;
	
	UFUNCTION()
	void SpawnPipe();

protected:
	
	virtual void BeginPlay() override;

};
