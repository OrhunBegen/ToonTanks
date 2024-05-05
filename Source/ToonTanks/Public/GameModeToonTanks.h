// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HealthComponent.h"
#include "GameModeToonTanks.generated.h"



/**
 * 
 */
UCLASS()
class TOONTANKS_API AGameModeToonTanks : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void ActorDied(AActor* DeadActor);
protected:
	virtual void BeginPlay() override;
	
private:
	class ATankCode* Tank;

	class ATanksPlayerController* TanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();


};
