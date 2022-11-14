// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/GameModes/OnYourOwnGameMode.h"
#include "AIController.h"
#include "EngineUtils.h"

AOnYourOwnGameMode::AOnYourOwnGameMode()
{
	PlayersNum = 5;
	RoundTime = 30;
}

void AOnYourOwnGameMode::StartPlay()
{
	Super::StartPlay();
	SpawnBots();
	StartRound();
	SetMatchState(EMatchState::EMS_GameInProgress);
}

UClass* AOnYourOwnGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnTPS;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AOnYourOwnGameMode::SpawnBots()
{
	if (!GetWorld()) return;
	for (int32 i = 0; i < PlayersNum - 1; ++i)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto CAIController = GetWorld()->SpawnActor<AAIController>(AIControllerTPS, ActorSpawnParameters);
		RestartPlayer(CAIController);
	}

}

void AOnYourOwnGameMode::StartRound()
{
	TimeLeft = RoundTime;
	GetWorldTimerManager().SetTimer(RoundTimer, this, &AOnYourOwnGameMode::UpdateTimer, 1.f, true);
}

void AOnYourOwnGameMode::UpdateTimer()
{
	TimeLeft--;
	UE_LOG(LogTemp, Error, TEXT("Time Left: %i"), TimeLeft);
	if (TimeLeft == 0)
	{
		GetWorldTimerManager().ClearTimer(RoundTimer);
		GameOver();
	}
}

void AOnYourOwnGameMode::Respawn(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}

void AOnYourOwnGameMode::SetMatchState(EMatchState State)
{
	if (MatchState == State) return;
	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

bool AOnYourOwnGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseCondition = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseCondition)
	{
		SetMatchState(EMatchState::EMS_OnPause);
	}
	return PauseCondition;
}

bool AOnYourOwnGameMode::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EMatchState::EMS_GameInProgress);
	}
	return PauseCleared;
}

void AOnYourOwnGameMode::GameOver()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	SetMatchState(EMatchState::EMS_GameOver);
}
