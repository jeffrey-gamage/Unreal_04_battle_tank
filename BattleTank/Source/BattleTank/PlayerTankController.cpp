// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTankController.h"
#include "Tank.h"

ATank* APlayerTankController::GetControlledTank() const
{
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		FString TankName = ControlledTank->GetName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTankController Tank not found"));
	}
	return ControlledTank;
}

void APlayerTankController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerTankController BeginPlay called"));
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
		GetSightRayHitLocation(OutHitLocation);

		//TODO: move barrel to aim towards target location
	}
}

void APlayerTankController::GetLookDirection(FVector2D &ScreenPosition)
{
	FVector CameraWorldLocation;//out param
	FVector CameraLookDirection;//out param
	DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, CameraWorldLocation, CameraLookDirection);
}

bool APlayerTankController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	OutHitLocation = FVector(99.f);
	FVector2D ScreenPosition = GetCrosshairScreenLocation();
	GetLookDirection(ScreenPosition);
	//TODO: ray cast from crosshairs to world target location
	//if collision with landscape or tank, set OutHitLocation to collision coordinates and return true
	//else return false
	return true;
}

FVector2D APlayerTankController::GetCrosshairScreenLocation()
{
	int32 VeiwportX, VeiwportY; //out params
	GetViewportSize(VeiwportX, VeiwportY);
	return FVector2D(VeiwportX*CrosshairXLocation, VeiwportY*CrosshairYLocation);
}