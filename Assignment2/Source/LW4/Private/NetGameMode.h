#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetAvatar.h"
#include "NetGameMode.generated.h"

/**
*/
UCLASS()
class ANetGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANetGameMode();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UFUNCTION(BlueprintCallable)
	void AvatarsOverlapped(ANetAvatar* AvatarA, ANetAvatar* AvatarB);

	UFUNCTION(BlueprintCallable)
	void EndGame();

	void Timer();
	
	UFUNCTION(BlueprintCallable)
	void RefreshTimer();

private:
	int TotalPlayerCount;
	int TotalGames;
	int PlayerStartIndex;
	int DurationOfTheGame;
	int TimeLeft;
		

	FTimerHandle TimeTimer;

	TArray<APlayerController*> AllPlayers;

	AActor* GetPlayerStart(FString Name, int Index);

	AActor* AssignTeamAndPlayerStart(AController* Player);
};