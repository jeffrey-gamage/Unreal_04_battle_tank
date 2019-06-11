// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::RotateTurretAndMoveBarrel(FVector NewBarrelDirection)
{
	//TODO: generate FRotator for turret direction
	//generate FRotator for barrel elevation
	auto BarrelDirection = BarrelReference->GetForwardVector().Rotation();
	auto DirectionToAim = NewBarrelDirection.Rotation();
	auto DeltaRotation = DirectionToAim - BarrelDirection;
	BarrelReference->ElevateBarrel(DeltaRotation.Pitch);
	TurretReference->RotateTurret(DeltaRotation.Yaw);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector NewTargetLocation, float ProjectileSpeed)
{
	if (!BarrelReference) { 
		UE_LOG(LogTemp, Warning, TEXT("barrel not found")); 
		return; }
	FVector OutProjectileVelocity;
	FVector StartLocation = BarrelReference->GetSocketLocation(FName("Muzzle"));
	bool HasFiringSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutProjectileVelocity,
		StartLocation,
		NewTargetLocation,
		ProjectileSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(HasFiringSolution)
	{
		RotateTurretAndMoveBarrel(OutProjectileVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	BarrelReference = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	TurretReference = TurretToSet;
}