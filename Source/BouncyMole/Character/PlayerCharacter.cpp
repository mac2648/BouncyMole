// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Module2D/FlipBook/FlipBookList.h"
#include "BouncyMole/GameMode/BouncyMoleGameMode.h"
#include "Kismet/GameplayStatics.h"

#define PUSH_FORCE 200
#define MAXIMUM_FORCE 3000

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanJump())
	{
		IsDrilling = false;
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	float MoveValue = Value.Get<float>();

	if (Controller)
	{
		AddControllerYawInput(MoveValue);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EnableAddForceAction, ETriggerEvent::Started, this, &APlayerCharacter::EnableAddForce);
		EnhancedInputComponent->BindAction(EnableAddForceAction, ETriggerEvent::Completed, this, &APlayerCharacter::DisableAddForce);
		EnhancedInputComponent->BindAction(AddForceAction, ETriggerEvent::Triggered, this, &APlayerCharacter::AddForce);
	}
}

void APlayerCharacter::AddForce(const FInputActionValue& Value)
{
	float ForceValue = Value.Get<float>();

	if (CanAddForce)
	{
		PushForce += ForceValue * PUSH_FORCE;

		if (PushForce < -MAXIMUM_FORCE)
		{
			PushForce = -MAXIMUM_FORCE;
		}
		else if (PushForce > 0)
		{
			PushForce = 0;
		}
	}
}

void APlayerCharacter::EnableAddForce(const FInputActionValue& Value)
{
	CanAddForce = true;
}

void APlayerCharacter::DisableAddForce(const FInputActionValue& Value)
{
	CanAddForce = false;

	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Add(0, 90, 0);
	FVector Direction = ControlRotation.Vector();
	Direction.Z = 0;
	Direction *= PushForce;

	Jump();
	GetCharacterMovement()->Velocity = Direction;

	PushForce = 0.0f;
}

void APlayerCharacter::UpdateAnimation(const FVector& CharVelocity)
{
	GetSprite()->SetFlipbook(BookList->Idle);
}

void APlayerCharacter::UpdateRotation(const FVector& CharVelocity)
{

}

void APlayerCharacter::TakeDamage()
{
	Hp -= 1;

	if (Hp <= 0)
	{
		if (ABouncyMoleGameMode* GameMode = Cast<ABouncyMoleGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GameMode->GameOver();
		}
	}
}