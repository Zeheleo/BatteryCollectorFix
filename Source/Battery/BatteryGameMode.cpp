// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryGameMode.h"
#include "BatteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABatteryGameMode::ABatteryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;

	// Set initial decay value
	decayRate = 0.03f;
}

void ABatteryGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Set the score to beat
	ABatteryCharacter* pCharacter = Cast<ABatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (pCharacter)
	{
		PowerToWin = (pCharacter->GetInitialPower()) * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABatteryGameMode::Tick(float dt)
{
	Super::Tick(dt);

	ABatteryCharacter* pCharacter = Cast<ABatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
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

float ABatteryGameMode::GetPowerToWin() const
{
	return PowerToWin;
}
