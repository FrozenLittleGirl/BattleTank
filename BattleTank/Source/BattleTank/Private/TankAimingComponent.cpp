// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/Turret.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed) {
	if (Barrel == nullptr) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool result = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LauchSpeed,
		false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
	);
    
    auto time = GetWorld()->GetTimeSeconds();
    
	if (result) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Find"), time);

        MoveBarrelAndTurret(AimDirection);
    } else {
        //UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Find"), time);
    }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurret* TurretToSet) {
    Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelAndTurret(FVector AimDirection) {
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	auto DeltaRotator = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
    
}
