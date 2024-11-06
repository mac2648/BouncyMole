// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "QueenEnemy.generated.h"

class APlayerCharacter;
class AMagicAttack;

UCLASS()
class BOUNCYMOLE_API AQueenEnemy : public ABasicEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* HitSound;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* MagicAnim;

	UPROPERTY(EditAnywhere, category = "Attack")
	TSubclassOf<AMagicAttack> MagicClass;

	UPROPERTY(EditAnywhere, category = "Attack")
	float AttackCD = 6;

	float CD = 6;
	int HP = 3;
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void CastMagic();
	void StartCastAnimation();

	UFUNCTION()
	void GetHappy(int Value);
};
