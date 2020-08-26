// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERY_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const
	{
		return PickupMesh;
	}

	/* Blueprint### -  expose native C++ functions to blueprints.
	BlueprintPure - Can modify things but should not / run everytime their output is used
					   if this function pops something off the stack -> called twice.
					fast calculation that frequently change
	*/
	/* BlueprintCallable - only run when the input execution pin is hit
	*						save result for output pin
	*						modifying cells
	*						Complicated functions
	*/

	// return the mesh for the pickup
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	// allows other classes to safely cahnge whether or not pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool state);

	// FUnction to call when the pickup is collected - override behavior of blueprint and code, this is an option
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

protected:
	// true when the pick can be used, and false when pickup is deactivated
	bool bIsActive;

private:
	// statuc mesh to represent the pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

};
