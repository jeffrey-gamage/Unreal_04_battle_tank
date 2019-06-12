// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"

ATank* APlayerTankController::GetControlledTank() const
{
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		FString TankName = ControlledTank->GetName();
	}
	return ControlledTank;
}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();
}

void APlayerTankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshairs();
}

void APlayerTankController::AimTowardCrosshairs()
{
	if (GetControlledTank())
	{
		FVector OutHitLocation;
		if (GetSightRayHitLocation(OutHitLocation))
		{
			GetControlledTank()->AimAt(OutHitLocation);
		}
	}
}

void APlayerTankController::GetLookDirection(FVector2D &ScreenPosition, FVector &CameraWorldLocation, FVector &CameraLookDirection)
{
	DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, CameraWorldLocation, CameraLookDirection);
}

bool APlayerTankController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	OutHitLocation = FVector(99.f);
	FVector2D ScreenPosition = GetCrosshairScreenLocation();
	FVector OutCameraWorldLocation;//out param
	FVector OutCameraLookDirection;//out param
	GetLookDirection(ScreenPosition,OutCameraWorldLocation,OutCameraLookDirection);
	FHitResult HitResult; //out param

	//TODO: ray cast from crosshairs to world target location
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult OutHitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		OutCameraWorldLocation,
		GetLineTraceEnd(OutCameraWorldLocation, OutCameraLookDirection),
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParams,
		FCollisionResponseParams()
	))
	{
		OutHitLocation = OutHitResult.Location;
		return true;
	}
	//if collision with landscape or tank, set OutHitLocation to collision coordinates and return true
	//else return false
	OutHitLocation = FVector(0.f);
	return false;
}

FVector2D APlayerTankController::GetCrosshairScreenLocation()
{
	int32 VeiwportX, VeiwportY; //out params
	GetViewportSize(VeiwportX, VeiwportY);
	return FVector2D(VeiwportX*CrosshairXLocation, VeiwportY*CrosshairYLocation);
}

FVector APlayerTankController::GetLineTraceEnd(FVector CameraWorldLocation, FVector CameraLookDirection)
{
	return CameraWorldLocation + LineTraceDistance * CameraLookDirection;
}