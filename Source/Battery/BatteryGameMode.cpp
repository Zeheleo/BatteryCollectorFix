// Copyright Epic Games, Inc. All Rights Reserved.

#include "BatteryGameMode.h"
#include "BatteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"

//#include "Components/SkeletalMeshcomponent.h"
#include "GameFramework/PawnMovementComponent.h" // MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;


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

	// find all spawn volume Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EBatteryPlayState::EPlaying);

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
		if (pCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}

		// If the character's power is positive
		else if (pCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the decay rate
			pCharacter->UpdatePower(-dt * decayRate * (pCharacter->GetInitialPower()));
		}

		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	HandleCurrentState(CurrentState);
}

void ABatteryGameMode::HandleCurrentState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
	case EBatteryPlayState::EPlaying:
	{
		// Spawn volume active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
	}
	break;
	
	case EBatteryPlayState::EWon:
	{
		// Spawn volume inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;
	
	case EBatteryPlayState::EGameOver:
	{
		// Spawn volume inactives
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}

		// block player input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}

		// ragdoll the characte
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if(MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;
	
	case EBatteryPlayState::EUnknown:
	{
		// Do nothing 
	}
	break;
	}
}
