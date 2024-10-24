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
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#define PUSH_FORCE 200.0f
#define MAXIMUM_FORCE 3000.0f

APlayerCharacter::APlayerCharacter()
{
	SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanJump() && IsDrilling)
	{
		StopDrilling();
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
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Pause);
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

void APlayerCharacter::StartDrilling()
{
	IsDrilling = true;
	if (!SoundComp->IsPlaying())
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting"))
		SoundComp->SetSound(DrillSound);
		SoundComp->Play();
	}
}

void APlayerCharacter::StopDrilling()
{
	UE_LOG(LogTemp, Warning, TEXT("STOPPING"))
	IsDrilling = false;
	SoundComp->Stop();
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

	OnPlayerTakeDamage.Broadcast(Hp);

	if (Hp <= 0)
	{
		if (ABouncyMoleGameMode* GameMode = Cast<ABouncyMoleGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GameMode->GameOver();
		}
	}
}

void APlayerCharacter::Pause()
{
	if (PauseWidgetClass)
	{
		UUserWidget* PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
		PauseWidget->AddToViewport();
	}
}

float APlayerCharacter::GetPushForcePercent() const
{
	return PushForce / MAXIMUM_FORCE;
}