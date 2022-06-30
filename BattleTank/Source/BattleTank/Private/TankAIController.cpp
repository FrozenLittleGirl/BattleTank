// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerController = GetPlayerTank();
	if (PlayerController == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AI does not find the player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI %s has found the player tank: %s"),
			*(ControlledTank->GetName()),
			*(PlayerController->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank != nullptr) {
		// TODO move towards the player


		// Aim towards the player
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

		// fire if ready

	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerController == nullptr) {
		return nullptr;
	}
	else {
		return Cast<ATank>(PlayerController);
	}
}