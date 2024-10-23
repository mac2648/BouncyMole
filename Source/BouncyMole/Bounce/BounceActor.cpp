// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceActor.h"
#include "Components/BoxComponent.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#define SPEED_LIMIT 3000

// Sets default values
ABounceActor::ABounceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ABounceActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABounceActor::Bounce);
}

void ABounceActor::Bounce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		/*
		The idea here is to find both angles by using the cos from the normalized vectors, and them with the distance between the two
		angles and with it find the exit angle and velocity. For now time does not allow to follow the idea, so later try out this approach
		
		FVector2D ImpactNormal(SweepResult.ImpactNormal.X, SweepResult.ImpactNormal.Y);

		FVector PlayerVel = Player->GetCharacterMovement()->Velocity;
		FVector2D PlayerVel2D(PlayerVel.X, PlayerVel.Y);

		PlayerVel2D.Normalize();
		ImpactNormal.Normalize();

		float PlayerVelAngle = GetAngleFromNormalizedVector(PlayerVel2D);
		float ImpactNormalAngle = GetAngleFromNormalizedVector(ImpactNormal);

		float AngleDiference = PlayerVelAngle - ImpactNormalAngle;

		UE_LOG(LogTemp, Warning, TEXT("%f"), AngleDiference);
		*/

		UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement();

		if (InvertX)
		{
			MoveComp->Velocity.X *= -1;
		}
		
		if (InvertY)
		{
			MoveComp->Velocity.Y *= -1;
		}

		MoveComp->Velocity.X *= SpeedMultiplier;
		MoveComp->Velocity.Y *= SpeedMultiplier;

		if (MoveComp->Velocity.Length() > 1400)
		{
			Player->IsDrilling = true;
		}

		if (MoveComp->Velocity.X > SPEED_LIMIT)
		{
			MoveComp->Velocity.X = SPEED_LIMIT;
		}
		if (MoveComp->Velocity.Y > SPEED_LIMIT)
		{
			MoveComp->Velocity.Y = SPEED_LIMIT;
		}
		if (MoveComp->Velocity.X < -SPEED_LIMIT)
		{
			MoveComp->Velocity.X = -SPEED_LIMIT;
		}
		if (MoveComp->Velocity.Y < -SPEED_LIMIT)
		{
			MoveComp->Velocity.Y = -SPEED_LIMIT;
		}
	}
}

float ABounceActor::GetAngleFromNormalizedVector(const FVector2D& Vec)
{
	float Angle = FMath::RadiansToDegrees(FMath::Asin(Vec.Y / FMath::Sqrt(FMath::Pow(Vec.Y, 2) + FMath::Pow(Vec.X, 2))));

	if (Angle < 0)
	{
		Angle = -Angle;
	}

	if (Vec.X < 0 && Vec.Y > 0)
	{
		Angle = 180 - Angle;
	}
	else if (Vec.X < 0 && Vec.Y < 0)
	{
		Angle = 180 + Angle;
	}
	else if (Vec.X > 0 && Vec.Y < 0)
	{
		Angle = 360 - Angle;
	}

	return Angle;
}