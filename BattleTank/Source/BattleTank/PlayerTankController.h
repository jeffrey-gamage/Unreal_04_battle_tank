// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "PlayerTankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EDITANYWHERE)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EDITANYWHERE)
		float CrosshairYLocation = 0.333333f;
	
private:
	FVector2D GetCrosshairScreenLocation();
	void AimTowardCrosshairs();
	void GetLookDirection(FVector2D &ScreenPosition);
	bool GetSightRayHitLocation(FVector& OutHitLocation);
};
