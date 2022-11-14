// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartPlayButton)
	{
		StartPlayButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
	}
}

void UMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;
	UGameplayStatics::OpenLevel(this, "OnYourOwn");
}