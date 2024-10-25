// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "BouncyMole/GameMode/BouncyMoleGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"

ABasicEnemy::ABasicEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(Capsule);
}

void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitialPosition = GetActorLocation();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		MasterCamera = Player->GetCameraComp();
	}
	else
	{
		throw "expected APlayerCharacter as the player class";
	}

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::Attack);
}

void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanMove && !IsDead)
	{
		Move(DeltaTime);
	}

	RotateToCamera();
}

void ABasicEnemy::Move(float DeltaTime)
{
	if (!IsGoingBack)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += MovementAmount * DeltaTime * Speed;
		SetActorLocation(CurrentLocation);
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation -= MovementAmount * DeltaTime * Speed;
		SetActorLocation(CurrentLocation);
	}

	FVector FinalPosition = InitialPosition + MovementAmount;

	if ((FinalPosition - GetActorLocation()).IsNearlyZero(20))
	{
		IsGoingBack = true;
	}
	else if ((InitialPosition - GetActorLocation()).IsNearlyZero(20))
	{
		IsGoingBack = false;
	}
}

void ABasicEnemy::Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (Player->GetIsDrilling())
		{
			Die();
		}
		else
		{
			Player->TakeDamage();

			FVector PlayerLocation = Player->GetActorLocation();
			FVector Direction = PlayerLocation - GetActorLocation();
			Direction.Normalize();
			Direction *= 200;
			Direction.Z = 0;

			Player->GetCharacterMovement()->Velocity = Direction;

			Sprite->SetFlipbook(Happy);

			FTimerHandle Handle;

			GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABasicEnemy::ChangeToIdle, 3.5);
		}
	}
}

void ABasicEnemy::Die()
{
	IsDead = true;

	if (ABouncyMoleGameMode* GameMode = Cast<ABouncyMoleGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->AddTime();
	}

	Sprite->SetFlipbook(Dead);
	Sprite->SetLooping(false);
	Sprite->OnFinishedPlaying.Clear();
	Sprite->OnFinishedPlaying.AddDynamic(this, &ABasicEnemy::Disapear);

	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void ABasicEnemy::ChangeToIdle()
{ 
	Sprite->SetFlipbook(Idle); 
}