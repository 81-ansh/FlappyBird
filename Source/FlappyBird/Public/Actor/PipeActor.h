// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> TopCollision;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BottomCollision;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> ScoreCollision;
	
	UPROPERTY(EditAnywhere, Category = "Pipe")
	float MoveSpeed = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "Pipe")
    float DestroyActor = -2000.f;
	
	UFUNCTION()
	void OnScoreOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
