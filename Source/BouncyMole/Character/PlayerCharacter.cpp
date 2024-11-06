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
#include "BouncyMole/Sprites/PlayerBookList.h"
#include "Module2D/Utils/Utils2D.h"

#define PUSH_FORCE 200.0f
#define MAXIMUM_FORCE 2300.0f

APlayerCharacter::APlayerCharacter()
{
	SoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));

	Arrow = CreateDefaultSubobject< UPaperFlipbookComponent>(TEXT("Arrow Comp"));
	Arrow->SetupAttachment(GetSprite());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);

	GetSprite()->SetFlipbook(BookList->Idle);

	PowerBar = CreateWidget<UUserWidget>(GetWorld(), PowerBarClass);
	PowerBar->AddToViewport();

	PowerBar->SetVisibility(ESlateVisibility::Hidden);
	PowerBar->UpdateCanTick();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanJump() && IsDrilling)
	{
		StopDrilling();
	}
	else if (CanJump() && GetSprite()->GetFlipbook() == BookList->Idle)
	{
		CanAct = true;
	}
	else if (CanJump() && GetSprite()->GetFlipbook() == Cast<UPlayerBookList>(BookList)->BounceNormal)
	{
		UUtils2D::PlayAnimationOnce(GetSprite(), Cast<UPlayerBookList>(BookList)->Rest, this, &APlayerCharacter::Land, "Land");
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
	if (CanAct)
	{
		CanAddForce = true;

		Arrow->SetFlipbook(Cast<UPlayerBookList>(BookList)->Arrow);

		PowerBar->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacter::DisableAddForce(const FInputActionValue& Value)
{
	CanAddForce = false;
	PowerBar->SetVisibility(ESlateVisibility::Hidden);

	Arrow->SetFlipbook(nullptr);

	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Add(0, 90, 0);
	FVector Direction = ControlRotation.Vector();
	Direction.Z = 0;
	Direction *= PushForce;

	if (Direction.Length() >= 20)
	{
		UUtils2D::PlayAnimationOnce(GetSprite(), Cast<UPlayerBookList>(BookList)->Launch, this, &APlayerCharacter::Dash, "Dash");

		FTimerHandle Handle;
		FTimerDelegate TimerFunc;
		TimerFunc.BindLambda([this, Direction]() {
				Jump();
				GetCharacterMovement()->Velocity = Direction;
				CanAct = false;
			});

		GetWorld()->GetTimerManager().SetTimer(Handle, TimerFunc, 0.19, false);
	}

	PushForce = 0.0f;
}

void APlayerCharacter::StartDrilling()
{
	IsDrilling = true;

	GetSprite()->SetFlipbook(Cast<UPlayerBookList>(BookList)->Drill);

	if (!SoundComp->IsPlaying())
	{
		SoundComp->SetSound(DrillSound);
		SoundComp->Play();
	}
}

void APlayerCharacter::StopDrilling()
{
	UUtils2D::PlayAnimationOnce(GetSprite(), Cast<UPlayerBookList>(BookList)->DrillLand, this, &APlayerCharacter::Land, "Land");

	IsDrilling = false;
	SoundComp->Stop();
}

void APlayerCharacter::SetCannotBounce(bool IsX)
{
	IsX ? CanBounceX = false : CanBounceY = false;

	FTimerHandle Handle;
	FTimerDelegate TimedLambda;
	TimedLambda.BindLambda([this, IsX]() {
			IsX ? CanBounceX = true : CanBounceY = true;
		});

	GetWorld()->GetTimerManager().SetTimer(Handle, TimedLambda, 0.025, false);
}

void APlayerCharacter::Land()
{
	GetSprite()->SetLooping(true);
	GetSprite()->SetFlipbook(Cast<UPlayerBookList>(BookList)->Idle);
	GetSprite()->Play();
	CanAct = true;
}

void APlayerCharacter::Dash()
{
	GetSprite()->SetFlipbook(Cast<UPlayerBookList>(BookList)->BounceNormal);
	GetSprite()->Play();
	GetSprite()->SetLooping(true);
}

void APlayerCharacter::UpdateAnimation(const FVector& CharVelocity)
{

}

void APlayerCharacter::UpdateRotation(const FVector& CharVelocity)
{

}

void APlayerCharacter::TakeDamage()
{
	Hp -= 1;

	UGameplayStatics::PlaySound2D(GetWorld(), TakeDamageSound);

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
	return -PushForce / MAXIMUM_FORCE;
}