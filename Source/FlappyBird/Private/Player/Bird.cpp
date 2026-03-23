// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Bird.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = false;
	
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
	Mesh->SetPhysicsLinearVelocity(FVector(0.f, 0.f, 600.f));
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
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedIC->BindAction(FlapAction, ETriggerEvent::Started, this, &ABird::Flap);
	}
}

