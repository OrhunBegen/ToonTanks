// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeToonTanks.h"
#include "TankCode.h"
#include "TanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"


void AGameModeToonTanks::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank -> HandleDestruction();
		if (TanksPlayerController)
		{
			TanksPlayerController -> SetPlayerEnabledState(false);
		}
		GameOver(false); // Player Died
		
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret -> HandleDestruction();
		--TargetTurrets;
		if (TargetTurrets == 0)
		{
			GameOver(true); // Player Won
		}
	}
}
void AGameModeToonTanks::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

void AGameModeToonTanks::HandleGameStart()
{
	TargetTurrets = GetTargetTurretsCount();
	Tank = Cast <ATankCode>(UGameplayStatics::GetPlayerPawn(this, 0));
	TanksPlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	
	if(TanksPlayerController)
	{
		TanksPlayerController -> SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(TanksPlayerController,&ATanksPlayerController::SetPlayerEnabledState,true );

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
		
	}
	
}
int32 AGameModeToonTanks::GetTargetTurretsCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}