// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Module2D/Interface/RotateToCamera.h"
#include "MagicAttack.generated.h"

UCLASS()
class BOUNCYMOLE_API AMagicAttack : public AActor, public IRotateToCamera
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Speed = 0.4;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, category = "Sprites")
	class UPaperFlipbook* Begin;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* Middle;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* End;

	FVector TargetDirection;

	bool HasHit = false;
	
public:	
	// Sets default values for this actor's properties
	AMagicAttack();
	void SetTarget(FVector NewTarget) { TargetDirection = NewTarget; TargetDirection.Normalize(); }

	UFUNCTION()
	void HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void GoMiddle();
	
	UFUNCTION()
	void Disapear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
