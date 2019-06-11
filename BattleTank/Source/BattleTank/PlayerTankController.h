// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.333333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceDistance = 5000.f;
	
private:
	FVector2D GetCrosshairScreenLocation();
	void AimTowardCrosshairs();
	void GetLookDirection(FVector2D &ScreenPosition,FVector &CameraWorldPosition, FVector &CameraLookDirection);
	bool GetSightRayHitLocation(FVector& OutHitLocation);
	FVector GetLineTraceEnd(FVector CameraWorldPosition, FVector CameraLookDirection);
};
