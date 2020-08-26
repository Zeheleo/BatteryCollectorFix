// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryGameMode.h"
#include "BatteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;

	// Set initial decay value
	decayRate = 0.01f;
}

void ABatteryCollectorGameMode::Tick(float dt)
{
	Super::Tick(dt);

	ABatteryCollectorCharacter* pCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (pCharacter)
	{
		// If the character's power is positive
		if (pCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the decay rate
			pCharacter->UpdatePower(-dt * decayRate * (pCharacter->GetInitialPower()));
		}
	}
}
