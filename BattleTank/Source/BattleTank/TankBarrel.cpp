// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed,(float)-1,(float)1);
	float DeltaElevation = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Pitch + DeltaElevation;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewRotation,MinElevationDegrees,MaxElevationDegrees),0,0));
}
