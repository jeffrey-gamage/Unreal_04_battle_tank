// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	//TODO: clamp throttle values so that control sensitivity doesn't affect tank speed.
	FVector ForceApplied = GetForwardVector() * throttle * MaxTrackForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}