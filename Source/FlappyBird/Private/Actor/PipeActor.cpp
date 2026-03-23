// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PipeActor.h"

APipeActor::APipeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	
	TopPipe = CreateDefaultSubobject<UStaticMeshComponent>("TopPipe");
	TopPipe->SetupAttachment(RootComponent);
	TopPipe->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BottomPipe = CreateDefaultSubobject<UStaticMeshComponent>("BottomPipe");
	BottomPipe->SetupAttachment(RootComponent);
	BottomPipe->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Direction = FVector(-(MoveSpeed * DeltaTime), 0.0f, 0.0f);
	AddActorWorldOffset(Direction);
}

