// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicEnemy.h"
#include "QueenEnemy.generated.h"

class APlayerCharacter;
class AMagicAttack;
class UWidgetComponent;

#define QueenRewardScore 20
#define QueenMaxHP 3

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueenHpChanged, float, Percent);

UCLASS()
class BOUNCYMOLE_API AQueenEnemy : public ABasicEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FQueenHpChanged OnQueenHpChange;

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* HitSound;

	UPROPERTY(EditAnywhere, category = "Sprites")
	UPaperFlipbook* MagicAnim;

	UPROPERTY(EditAnywhere, category = "Attack")
	TSubclassOf<AMagicAttack> MagicClass;

	UPROPERTY(EditAnywhere, category = "Attack")
	float AttackCD = 6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar;

	float CD = 6;
	int HP = QueenMaxHP;
	
public:
	AQueenEnemy();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void CastMagic();
	void StartCastAnimation();

	UFUNCTION()
	void GetHappy(int Value);
};
