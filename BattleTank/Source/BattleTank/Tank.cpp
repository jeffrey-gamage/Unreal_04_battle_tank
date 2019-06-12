// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Tick(float DeltaTimeSeconds)
{
	Super::Tick(DeltaTimeSeconds);
	if (TimeUntilReloaded > 0.f)
	{
		TimeUntilReloaded -= DeltaTimeSeconds;
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector TargetLocation)
{
	TankAimingComponent->AimAt(TargetLocation,LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	if (TimeUntilReloaded <= 0.f)
	{
		auto TankShell = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Muzzle")), Barrel->GetSocketRotation(FName("Muzzle")));
		TankShell->LaunchProjectile(LaunchSpeed);
		TimeUntilReloaded = ReloadTime;
	}
}
