// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERY_API ABatteryPickup : public APickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABatteryPickup();

	// Override the wasCollectedFunction - use implementation because it's a blueprint native event
	void WasCollected_Implementation() override;

	// Public way to access the battery's power level
	float GetPower();

protected:
	//void BeginPlay();

	// Set the amount of power the attery gives to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true")) // Only blueprint can access here
	float BatteryPower;
};
