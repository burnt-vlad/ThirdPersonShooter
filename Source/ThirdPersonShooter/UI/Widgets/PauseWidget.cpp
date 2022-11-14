// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/PauseWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void UPauseWidget::NativeOnInitialized()
{
	const auto InitStatus = Super::Initialize();
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResume);
	}
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResetLevel);
	}
}

void UPauseWidget::OnResume()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UPauseWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}