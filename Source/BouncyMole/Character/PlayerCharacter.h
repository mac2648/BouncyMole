// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module2D/Character/Character2D.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOUNCYMOLE_API APlayerCharacter : public ACharacter2D
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* AddForceAction;

	UPROPERTY(EditDefaultsOnly, category = "Input")
	UInputAction* EnableAddForceAction;

private:

	float PushForce = 0.0f;
	bool CanAddForce = false;
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void Move(const FInputActionValue& Value) override;
	virtual void UpdateAnimation(const FVector& CharVelocity) override;
	virtual void UpdateRotation(const FVector& CharVelocity) override;

private:
	void AddForce(const FInputActionValue& Value);
	void EnableAddForce(const FInputActionValue& Value);
	void DisableAddForce(const FInputActionValue& Value);
};