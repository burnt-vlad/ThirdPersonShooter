// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/HUDs/BaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "ThirdPersonShooter/GameModes/OnYourOwnGameMode.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::EMS_GameInProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::EMS_OnPause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EMatchState::EMS_GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GetWorld())
	{
		const auto GameMode = Cast<AOnYourOwnGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ABaseHUD::OnMatchStateChanged);
		}
	}
}

void ABaseHUD::OnMatchStateChanged(EMatchState State)
{
	//UE_LOG(LogTemp, Error, TEXT("MatchState: %s"), *UEnum::GetValueAsString(State));
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}