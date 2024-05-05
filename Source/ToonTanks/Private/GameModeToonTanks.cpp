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
		
	}
	else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret -> HandleDestruction();
	}
	
	
}
void AGameModeToonTanks::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

void AGameModeToonTanks::HandleGameStart()
{
	Tank = Cast <ATankCode>(UGameplayStatics::GetPlayerPawn(this, 0));
	TanksPlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	if(TanksPlayerController)
	{
		TanksPlayerController -> SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(TanksPlayerController,&ATanksPlayerController::SetPlayerEnabledState,true );

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
		
	}
	
	


	


}
