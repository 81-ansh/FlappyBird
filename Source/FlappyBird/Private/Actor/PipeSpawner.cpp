// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PipeSpawner.h"


APipeSpawner::APipeSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APipeSpawner::SpawnPipe()
{
	
	float ZOffset = FMath::RandRange(ZOffsetMin, ZOffsetMax);
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z = ZOffset;
	GetWorld()->SpawnActor<APipeActor>(PipeSpawnClass, SpawnLocation, FRotator::ZeroRotator);
}

void APipeSpawner::StopSpawning()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void APipeSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &APipeSpawner::SpawnPipe, SpawnInterval, true);
}

