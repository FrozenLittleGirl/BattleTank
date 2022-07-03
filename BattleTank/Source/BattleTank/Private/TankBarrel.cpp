// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
    
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = MaxDegreePerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
    auto NewElevation = GetRelativeRotation().Pitch + ElevationChange;
    
    auto Elevation = FMath::Clamp<float>(NewElevation, MinElevationDegree, MaxElevationDegree);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}
