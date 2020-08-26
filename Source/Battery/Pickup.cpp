// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsActive = true; // All pickups has active

    // Create the static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// return active state
bool APickup::IsActive()
{
	return bIsActive;
}

// set state of pickup
void APickup::SetActive(bool state)
{
	bIsActive = state;
}

void APickup::WasCollected_Implementation()
{
	FString PickUpDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickUpDebugString);
}
