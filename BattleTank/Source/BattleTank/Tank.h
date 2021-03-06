// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTimeSeconds) override;
	UTankAimingComponent* TankAimingComponent;



public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable,Category=Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 5000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> Projectile= nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTime = 3.f;

	float TimeUntilReloaded = 0.f;
	UTankBarrel* Barrel;
};
