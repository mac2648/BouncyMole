// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasicEnemy.generated.h"

class UPaperFlipbookComponent;
class UCapsuleComponent;

UCLASS()
class BOUNCYMOLE_API ABasicEnemy : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, category = "Movement")
	FVector MovementAmount;

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 0.3;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* Sprite;

	UPROPERTY(EditAnywhere, category = "Movement")
	bool CanMove = false;

	bool IsGoingBack = false;
	FVector InitialPosition;

public:
	ABasicEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;
	void Move(float DeltaTime);
};
