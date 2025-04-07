// Fill out your copyright notice in the Description page of Project Settings.


#include "QueenEnemy.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BouncyMole/Actor/MagicAttack.h"
#include "Sound/SoundCue.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Module2D/Utils/Utils2D.h"
#include "BouncyMole/BouncyMoleGameInstance.h"

void AQueenEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Player->OnPlayerTakeDamage.AddDynamic(this, &AQueenEnemy::GetHappy);
	}
}

void AQueenEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead)
	{
		if (CD <= 0)
		{
			StartCastAnimation();
			CD = AttackCD;
		}
		else
		{
			CD -= DeltaTime;
		}
		Sprite->Play();
	}
}

void AQueenEnemy::Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (Player->GetIsDrilling())
		{
			GetGameInstance<UBouncyMoleGameInstance>()->AddScore(QueenRewardScore, ScoreType::QueenSlimeGain);
			HP--;
			if (HP <= 0)
			{
				GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
				ABasicEnemy::Die();
			}
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		else if (!Player->GetIsInvunerable())
		{
			Player->TakeDamage();
			GetGameInstance<UBouncyMoleGameInstance>()->AddScore(-QueenRewardScore, ScoreType::QueenSlimeLost);

			FVector PlayerLocation = Player->GetActorLocation();
			FVector Direction = PlayerLocation - GetActorLocation();
			Direction.Normalize();
			Direction *= 200;
			Direction.Z = 0;

			Player->GetCharacterMovement()->Velocity = Direction;

			Sprite->SetFlipbook(Happy);

			FTimerHandle Handle;

			GetWorld()->GetTimerManager().SetTimer(Handle, this, &AQueenEnemy::ChangeToIdle, 3.5);
		}
	}
}

void AQueenEnemy::CastMagic()
{
	FVector SpawnLocation = GetActorLocation() + GetActorRightVector() * 50;

	AMagicAttack* MAttack = GetWorld()->SpawnActor<AMagicAttack>(MagicClass, SpawnLocation, FRotator::ZeroRotator);

	if (MAttack)
	{
		MAttack->SetTarget(UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation() - GetActorLocation());
	}
}

void AQueenEnemy::StartCastAnimation()
{
	UUtils2D::PlayAnimationOnce(Sprite, MagicAnim, this, &AQueenEnemy::ChangeToIdle, "ChangeToIdle");

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AQueenEnemy::CastMagic, 0.6);
}

void AQueenEnemy::GetHappy(int Value)
{
	Sprite->SetFlipbook(Happy);

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AQueenEnemy::ChangeToIdle, 3);
}