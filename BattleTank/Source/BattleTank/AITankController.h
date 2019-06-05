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
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsPlayer();
};
