// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("tank player controller not possesed"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("tank player controller possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (GetControlledTank() == nullptr) { return; }

	FVector HitLocation;   // OUT parameter
	if (GetSightRayHitLocaiton(HitLocation)) {
        //UE_LOG(LogTemp, Warning, TEXT("is Aiming at: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
    } else {
        //UE_LOG(LogTemp, Warning, TEXT("Aiming cannot reach"));
    }
}

bool ATankPlayerController::GetSightRayHitLocaiton(FVector& OutHitLocation) const {
	// find the corsshair position
	int32 ViewPortX, ViewPortY;
	GetViewportSize(ViewPortX, ViewPortY);
	auto ScreenLocation = FVector2D(ViewPortX * CrossHairXLocation, ViewPortY * CrossHairYLocation);

	// De-Project
	FVector WorldDirection;
    bool result = false;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		result = GetLookVectorHitLocation(OutHitLocation, WorldDirection);
	}


	return result;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation;		// to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector WorldDirection) const {
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + WorldDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	return false;
}
