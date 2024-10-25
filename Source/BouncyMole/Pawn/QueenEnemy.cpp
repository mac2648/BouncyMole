// Fill out your copyright notice in the Description page of Project Settings.


#include "QueenEnemy.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BouncyMole/Actor/MagicAttack.h"
#include "Sound/SoundCue.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

void AQueenEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CD <= 0)
	{
		CastMagic();
		CD = AttackCD;
	}
	else
	{
		CD -= DeltaTime;
	}
}

void AQueenEnemy::Attack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (Player->GetIsDrilling())
		{
			HP--;
			if (HP <= 0)
			{
				GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
				ABasicEnemy::Die();
			}
			UE_LOG(LogTemp, Warning, TEXT("%d"), HP)
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
		MAttack->SetTarget(UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation());
	}
	
	Sprite->SetFlipbook(MagicAnim);
	Sprite->SetLooping(false);
	Sprite->OnFinishedPlaying.Clear();
	Sprite->OnFinishedPlaying.AddDynamic(this, &AQueenEnemy::ChangeToIdle);
}