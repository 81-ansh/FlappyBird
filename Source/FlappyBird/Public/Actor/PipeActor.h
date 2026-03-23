// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"

UCLASS()
class FLAPPYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APipeActor();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> TopPipe;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BottomPipe;
	
	UPROPERTY(EditAnywhere, Category = "Pipe")
	float MoveSpeed = 300.f;
	
	
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
