// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, (float)-1, (float)1);
	float DeltaElevation = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + DeltaElevation;
	SetRelativeRotation(FRotator(0,RawNewRotation,0));
}
