// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/PlayerControllers/PlayerControllerTPS.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonShooter/GameModes/OnYourOwnGameMode.h"

void APlayerControllerTPS::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &APlayerControllerTPS::PauseGame);
}

void APlayerControllerTPS::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto GameMode = Cast<AOnYourOwnGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &APlayerControllerTPS::OnMatchStateChanged);
		}
	}
}

void APlayerControllerTPS::PauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void APlayerControllerTPS::OnMatchStateChanged(EMatchState State)
{
    if (State == EMatchState::EMS_GameInProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}