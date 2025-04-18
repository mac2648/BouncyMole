// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Module2D/Interface/RotateToCamera.h"
#include "BasicEnemy.generated.h"

class UPaperFlipbookComponent;
class UCapsuleComponent;
class USoundCue;
class UPaperFlipbook;

//queen is not in the list because she has her own functions where the score is added
UENUM(BlueprintType)
enum EEnemyType
{
	GreenSlime,
	BlueSlime
};

UCLASS()
class BOUNCYMOLE_API ABasicEnemy : public APawn, public IRotateToCamera
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, category = "Movement")
	FVector MovementAmount;

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 0.3;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* WalkSound;

	UPROPERTY()
	UAudioComponent* SoundComp;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* Dead;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* Happy;

	UPROPERTY(EditAnywhere, category = "Movement")
	bool CanMove = false;

	UPROPERTY(EditAnywhere, category = "Sprites")
	TEnumAsByte<EEnemyType> Type;

	bool IsGoingBack = false;
	bool IsDead = false;
	FVector InitialPosition;

public:
	ABasicEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;
	void Die();

	void Move(float DeltaTime);

	UFUNCTION()
	virtual void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Disapear() { Destroy(); }

	UFUNCTION()
	void ChangeToIdle();
};
