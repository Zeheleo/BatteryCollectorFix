// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryGameMode();
	virtual void Tick(float deltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float decayRate;
};



