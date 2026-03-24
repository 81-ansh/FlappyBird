// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PipeActor.h"

#include "Game/FBGameMode.h"
#include "Kismet/GameplayStatics.h"

APipeActor::APipeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	
	TopPipe = CreateDefaultSubobject<UStaticMeshComponent>("TopPipe");
	TopPipe->SetupAttachment(RootComponent);
	TopPipe->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	TopCollision = CreateDefaultSubobject<UBoxComponent>("TopCollision");
	TopCollision->SetupAttachment(TopPipe);
	TopCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TopCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TopCollision->ComponentTags.Add(TEXT("Pipe"));
	
	BottomPipe = CreateDefaultSubobject<UStaticMeshComponent>("BottomPipe");
	BottomPipe->SetupAttachment(RootComponent);
	BottomPipe->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BottomCollision = CreateDefaultSubobject<UBoxComponent>("BottomCollision");
	BottomCollision->SetupAttachment(BottomPipe);
	BottomCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BottomCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BottomCollision->ComponentTags.Add(TEXT("Pipe"));
	
	ScoreCollision = CreateDefaultSubobject<UBoxComponent>("ScoreCollision");
	ScoreCollision->SetupAttachment(RootComponent);
}

void APipeActor::OnScoreOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGameMode* GameMode = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddScore();
	}
}

void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	
	ScoreCollision->OnComponentBeginOverlap.AddDynamic(this, &APipeActor::OnScoreOverlap);
}

void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Direction = FVector(-(MoveSpeed * DeltaTime), 0.0f, 0.0f);
	AddActorWorldOffset(Direction);
}

