// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnResetLevel);
	}
}

void UGameOverWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}