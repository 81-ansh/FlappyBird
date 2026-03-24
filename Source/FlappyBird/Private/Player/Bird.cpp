// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Bird.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actor/PipeActor.h"
#include "Actor/PipeSpawner.h"
#include "Game/FBGameMode.h"
#include "Kismet/GameplayStatics.h"


ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->BodyInstance.bLockYTranslation = true;
	Mesh->BodyInstance.bLockXTranslation = true;
	Mesh->BodyInstance.bLockZRotation = true;
	Mesh->BodyInstance.bLockXRotation = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

}

void ABird::Flap(const FInputActionValue& Value)
{
	Mesh->SetPhysicsLinearVelocity(FVector(0.f, 0.f, ZBoost));
}

void ABird::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the collision is Pipe
	if (OtherActor->IsA<APipeActor>() && OtherComp->ComponentTags.Contains(TEXT("Pipe")))
	{
		bIsDead = true;
		Die();
	}
}

void ABird::Die()
{
	// Disable Inputs
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->DisableInput(PC);
	}
	
	// Stop Pipes from moving
	TArray<AActor*> Pipes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APipeActor::StaticClass(), Pipes);
	for (AActor* Pipe : Pipes)
	{
		Pipe->SetActorTickEnabled(false);
	}
	
	// Stop Spawning
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APipeSpawner::StaticClass(), Spawners);
	if (Spawners.Num() > 0)
	{
		Cast<APipeSpawner>(Spawners[0])->StopSpawning();
	}
		
	AFBGameMode* GameMode = Cast<AFBGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->OnBirdDied();
	}
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABird::OnOverlapBegin);
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) return;
	
	FVector Location = GetActorLocation();
	if (Location.Z < MinZ || Location.Z > MaxZ)
	{
		Die();
	}
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedIC->BindAction(FlapAction, ETriggerEvent::Started, this, &ABird::Flap);
	}
}

