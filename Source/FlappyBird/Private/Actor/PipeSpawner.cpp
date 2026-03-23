// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PipeSpawner.h"


APipeSpawner::APipeSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APipeSpawner::SpawnPipe()
{
	float ZOffset = FMath::RandRange(ZOffsetMin, ZOffsetMax);
	GetWorld()->SpawnActor<APipeActor>(PipeSpawnClass, FVector(0.f, 0.f, ZOffset), FRotator::ZeroRotator);
}

void APipeSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &APipeSpawner::SpawnPipe, SpawnInterval, true);
}

