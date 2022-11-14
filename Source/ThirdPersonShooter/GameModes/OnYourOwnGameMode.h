// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "OnYourOwnGameMode.generated.h"

class AAIController;

UCLASS()
class THIRDPERSONSHOOTER_API AOnYourOwnGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AOnYourOwnGameMode();
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	void Respawn(AController* Controller);
	FOnMatchStateChanged OnMatchStateChanged;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Properties")
		TSubclassOf<AAIController> AIControllerTPS;
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Properties")
		TSubclassOf<APawn> AIPawnTPS;
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Properties")
		int32 PlayersNum;
	UPROPERTY(EditDefaultsOnly, Category = "Game Mode Properties")
		int32 RoundTime;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause());
	virtual bool ClearPause() override;

private:
	FTimerHandle RoundTimer;
	int32 TimeLeft;
	EMatchState MatchState = EMatchState::EMS_WaitingForTheStart;

	void SpawnBots();
	void StartRound();
	void UpdateTimer();
	void SetMatchState(EMatchState State);
	void GameOver();

public:
	int32 GetTimeRemaining() const { return TimeLeft; }
};
