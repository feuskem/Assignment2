// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameState.h"
#include "NetPlayerState.h"
#include "NetGameMode.h"
#include "NetBaseCharacter.h"
#include "Net/UnrealNetwork.h"





void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&
	OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetGameState, WinningPlayer);
}

ANetGameState::ANetGameState() :
	WinningPlayer(-1),
	Timer(30.0f)
	
{

}

void ANetGameState::OnRep_Winner()
{
	if (WinningPlayer >= 0)
	{
		OnVictory();
	}
}



void ANetGameState::TriggerRestart_Implementation()
{
	OnRestart();
}

ANetPlayerState* ANetGameState::GetPlayerStateByIndex(int PlayerIndex)
{

	for (APlayerState* PS : PlayerArray)
	{
		ANetPlayerState* State = Cast<ANetPlayerState>(PS);
		if (State && State->PlayerIndex == PlayerIndex)
		{
			return State;
		}
	}
	return nullptr;
}


