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
	virtual void Move(const FInputActionValue& Value) override;
};
