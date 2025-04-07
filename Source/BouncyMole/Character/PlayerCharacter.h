// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module2D/Character/Character2D.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerTakeDamage, int, CurrentHp);

#define MAX_HP 3;

class USoundCue;

UCLASS()
class BOUNCYMOLE_API APlayerCharacter : public ACharacter2D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPlayerTakeDamage OnPlayerTakeDamage;

protected:
	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* AddForceAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* EnableAddForceAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* PauseAction;

	UPROPERTY(EditDefaultsOnly, category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditdefaultsOnly, category = "Sound")
	USoundCue* DrillSound;

	UPROPERTY(EditdefaultsOnly, category = "Sound")
	USoundCue* TakeDamageSound;

	UPROPERTY()
	UAudioComponent* SoundComp;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* Arrow;

	UPROPERTY(EditAnywhere, category = "UI")
	TSubclassOf<UUserWidget> PowerBarClass;

	UPROPERTY()
	UUserWidget* PowerBar;

private:

	float PushForce = 0.0f;
	short Hp = MAX_HP;
	bool CanAddForce = false;
	bool IsDrilling = false;
	bool CanAct = true;
	bool CanBounceX = true;
	bool CanBounceY = true;
	bool IsInvunerable = false;
	
public:
	APlayerCharacter();

	UFUNCTION(BlueprintCallable)
	int GetCurrentHp() const { return Hp; }

	UFUNCTION(BlueprintCallable)
	float GetPushForce() const { return PushForce; }

	UFUNCTION(BlueprintCallable)
	float GetPushForcePercent() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void TakeDamage();
	inline bool GetIsDrilling() const { return IsDrilling; }
	inline bool GetIsInvunerable() const { return IsInvunerable; }
	virtual void Tick(float DeltaTime) override;
	void StartDrilling();
	void StopDrilling();
	void SetCannotBounce(bool IsX);
	bool GetCanBounce(bool IsX) const { return IsX? CanBounceX : CanBounceY; }

protected:
	virtual void BeginPlay() override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void UpdateAnimation(const FVector& CharVelocity) override;
	virtual void UpdateRotation(const FVector& CharVelocity) override;

	UFUNCTION()
	void Land();

	UFUNCTION()
	void Dash();

	UFUNCTION()
	void BecomeVunerable();

private:
	void AddForce(const FInputActionValue& Value);
	void EnableAddForce(const FInputActionValue& Value);
	void DisableAddForce(const FInputActionValue& Value);
	void Pause();
};
