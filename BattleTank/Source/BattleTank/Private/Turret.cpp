// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

void UTurret::Rotate(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto RotationChange = MaxDegreePerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = GetRelativeRotation().Yaw + RotationChange;
    SetRelativeRotation(FRotator(0, NewRotation, 0));
}
