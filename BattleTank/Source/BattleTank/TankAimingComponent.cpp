// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
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

void UTankAimingComponent::MoveBarrel(FVector NewBarrelDirection)
{
	//TODO: generate FRotator for turret direction
	//generate FRotator for barrel elevation
	auto BarrelDirection = BarrelReference->GetForwardVector().Rotation();
	auto DirectionToAim = NewBarrelDirection.Rotation();
	auto DeltaRotation = DirectionToAim - BarrelDirection;
	UE_LOG(LogTemp, Warning, TEXT("move barrel %s"), *DeltaRotation.ToString());
		//TODO: Create Barrel Class to control min/max elevation, elevation speed
		//TODO: move barrel the right amount this frame
	//TODO: apply FRotator to turret 
	//apply FRotator to barrel
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
		MoveBarrel(OutProjectileVelocity.GetSafeNormal());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("failed to generate firing solution"));
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	BarrelReference = BarrelToSet;
}

