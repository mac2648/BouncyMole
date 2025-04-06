#include "MagicAttack.h"
#include "BouncyMole/Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Module2D/Utils/Utils2D.h"
#include "BouncyMole/BouncyMoleGameInstance.h"
#include "BouncyMole/Pawn/QueenEnemy.h"

// Sets default values
AMagicAttack::AMagicAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(SphereComp);

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void AMagicAttack::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		MasterCamera = Player->GetCameraComp();
	}
	else
	{
		throw "expected APlayerCharacter as the player class";
	}

	UUtils2D::PlayAnimationOnce(Sprite, Begin, this, &AMagicAttack::GoMiddle, "GoMiddle");

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicAttack::HitTarget);
}

// Called every frame
void AMagicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateToCamera();

	if (!HasHit)
	{
		FVector Location = GetActorLocation() + TargetDirection * DeltaTime * Speed;
		SetActorLocation(Location);
	}
}

void AMagicAttack::HitTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (!Player->GetIsDrilling())
		{
			Player->TakeDamage();
			GetGameInstance<UBouncyMoleGameInstance>()->AddScore(-QueenRewardScore);
		}
	}
	
	HasHit = true;
	UUtils2D::PlayAnimationOnce(Sprite, End, this, &AMagicAttack::Disapear, "Disapear");
}

void AMagicAttack::Disapear()
{
	Destroy();
}

void AMagicAttack::GoMiddle()
{
	Sprite->SetFlipbook(Middle);
	Sprite->SetLooping(true);
}