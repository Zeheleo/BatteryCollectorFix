// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"

// Set Default values
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	// the base power level of battery
	BatteryPower = 150.f;
}

//void ABatteryPickup::BeginPlay()
//{
//	GetMesh()->SetSimulatePhysics(true);
//}

void ABatteryPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();

	// Destroy the battery
	Destroy();
}

// return power level of battery
float ABatteryPickup::GetPower()
{
	return BatteryPower;
}
