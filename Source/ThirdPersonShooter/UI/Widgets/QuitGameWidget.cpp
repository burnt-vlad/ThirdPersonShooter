// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/QuitGameWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UQuitGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UQuitGameWidget::OnQuitGame);
	}
}

void UQuitGameWidget::OnQuitGame()
{
	UE_LOG(LogTemp, Error, TEXT("OnQuitGame"));
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
