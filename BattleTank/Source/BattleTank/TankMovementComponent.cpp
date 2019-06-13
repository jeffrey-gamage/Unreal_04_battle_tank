// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing a track!"));
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool BforceMaxSpeed)
{
	FString MoverName = GetOwner()->GetName();
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto RequestedMoveVector = MoveVelocity.GetSafeNormal();
	auto RequestedThrow = FVector::DotProduct(TankForwardVector, MoveVelocity);
	UE_LOG(LogTemp, Warning, TEXT("%s Moving with Throw: %f"), *MoverName, RequestedThrow);
	IntendMoveForward(RequestedThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	Throw = FMath::Clamp(Throw, -1.f, 1.f);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	Throw = FMath::Clamp(Throw, -1.f, 1.f);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1.f*Throw);
}