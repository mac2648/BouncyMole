// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "InputActionValue.h"

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	float MoveValue = Value.Get<float>();

	if (Controller)
	{
		AddControllerYawInput(MoveValue);
	}
}