// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (result) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s is aiming at %s"), *(GetOwner()->GetName()), *HitLocation.ToString());

		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("Barrel Location: %s"), *(BarrelLocation.ToString()));

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	auto DeltaRotator = AimRotation - BarrelRotation;

	Barrel->Elevate(5);
}