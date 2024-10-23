// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Module2D/FlipBook/FlipBookList.h"
#include "Camera/CameraComponent.h"

#define PUSH_FORCE 200;

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

		UE_LOG(LogTemp, Warning, TEXT("Force = %f"), PushForce);
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