// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category= "Tech")
	float FireRange = 500.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class ATankCode* Tank;


	FTimerHandle FireRateTimerHandle;

	float FireRate = 2.f;
	
	void CheckFireCondition();

	bool InFireRange();
};
