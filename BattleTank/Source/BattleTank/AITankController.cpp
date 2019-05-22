// Fill out your copyright notice in the Description page of Project Settings.


#include "AITankController.h"
#include "PlayerTankController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"

ATank* AAITankController::GetControlledTank() const
{
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		FString TankName = ControlledTank->GetName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank not found"));
	}
	return ControlledTank;
}

ATank* AAITankController::GetPlayerTank() const
{
	APlayerTankController* PlayerTankController = Cast<APlayerTankController>(GetWorld()->GetFirstPlayerController());
	if (PlayerTankController)
	{
		ATank* ControlledTank = PlayerTankController->GetControlledTank();
		if (ControlledTank)
		{
			FString TankName = ControlledTank->GetName();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AITankController Tank not found"));
		}
		return ControlledTank;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController Player Controller not found"));
		return nullptr;
	}
}

void AAITankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO: Move
	AimTowardsPlayer();
	//TODO: Fire when ready
}

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AITankController BeginPlay called"));
}

void AAITankController::AimTowardsPlayer()
{
	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank&&ControlledTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
}