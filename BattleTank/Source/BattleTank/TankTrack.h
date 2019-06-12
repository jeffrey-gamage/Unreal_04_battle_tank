// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to apply forces to navigate a tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//set throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float MaxTrackForce= 200000;
};
