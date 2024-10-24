#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RotateToCamera.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URotateToCamera : public UInterface
{
	GENERATED_BODY()
};

class UCameraComponent;

class MODULE2D_API IRotateToCamera
{
	GENERATED_BODY()

protected:
	UCameraComponent* MasterCamera;


protected:
	void RotateToCamera();
	void RotateToCamera(UCameraComponent* Camera);
};
