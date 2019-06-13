// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITankController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API AAITankController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//TODO: check best protection level


private:
	void AimTowardsPlayer();
	ATank* ControlledTank;
	ATank* PlayerTank;

	//How close can the AI tank get to the player
	float AcceptanceRadius = 3000.f;
};
