// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/BackToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBackToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BackToMainMenuButton)
	{
		BackToMainMenuButton->OnClicked.AddDynamic(this, &UBackToMenuWidget::OnBackToMainMenu);
	}
}

void UBackToMenuWidget::OnBackToMainMenu()
{
	if (!GetWorld()) return;
	UGameplayStatics::OpenLevel(this, "MenuLevel");
}
