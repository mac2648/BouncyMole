// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BounceActor.generated.h"

class UBoxComponent;
class USoundCue;

UCLASS()
class BOUNCYMOLE_API ABounceActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	//1.0 is no multiplier
	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 1.2f;

	UPROPERTY(EditAnywhere)
	USoundCue* BounceSound;

	UPROPERTY(EditAnywhere)
	bool InvertX = false;

	UPROPERTY(EditAnywhere)
	bool InvertY = false;

	class APlayerCharacter* Player = nullptr;
	FVector LastHitFace;

public:	
	// Sets default values for this actor's properties
	ABounceActor();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Bounce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Clear(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float GetAngleFromNormalizedVector(const FVector2D& Vec);
};
