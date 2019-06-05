// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void RotateTurret(float RelativeSpeed); // -1 for max left, +1 for max right

private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 15.f;
};
