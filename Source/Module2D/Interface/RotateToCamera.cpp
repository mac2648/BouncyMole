#include "RotateToCamera.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

void IRotateToCamera::RotateToCamera()
{
	RotateToCamera(MasterCamera);
}

void IRotateToCamera::RotateToCamera(UCameraComponent* Camera)
{
	if (AActor* Actor = Cast<AActor>(this))
	{
		FVector CameraLocation = Camera->GetComponentLocation();
		FVector CurrentLocation = Actor->GetActorLocation();

		FVector Direction = CurrentLocation - CameraLocation;
		FRotator Rotation = Direction.Rotation();

		Rotation.Pitch = Actor->GetActorRotation().Pitch;
		Rotation.Roll = Actor->GetActorRotation().Roll;
		Rotation.Yaw += 90;

		Actor->SetActorRotation(Rotation);
	}
}