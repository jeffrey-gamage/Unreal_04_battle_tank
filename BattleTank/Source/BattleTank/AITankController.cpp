// Fill out your copyright notice in the Description page of Project Settings.


#include "AITankController.h"
#include "PlayerTankController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"


void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		MoveToActor(PlayerTank,AcceptanceRadius,true,true,false);
		AimTowardsPlayer();
		ControlledTank->Fire();
	}
}

void AAITankController::BeginPlay()
{
	Super::BeginPlay(); 
	ControlledTank = Cast<ATank>(GetPawn());
	APlayerTankController* PlayerTankController = Cast<APlayerTankController>(GetWorld()->GetFirstPlayerController());
	if (PlayerTankController)
	{
		PlayerTank = PlayerTankController->GetControlledTank();
	}
}

void AAITankController::AimTowardsPlayer()
{
	if (PlayerTank&&ControlledTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
}