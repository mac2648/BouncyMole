// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemy.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "BouncyMole/Character/PlayerCharacter.h"

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

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::Attack);
}

void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanMove)
	{
		Move(DeltaTime);
	}
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
			Destroy();
		}
		else
		{
			Player->TakeDamage();
		}
	}
}