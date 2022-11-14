// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/UI/Widgets/TimerWidget.h"
#include "ThirdPersonShooter/GameModes/OnYourOwnGameMode.h"

int32 UTimerWidget::GetTimeRemaining() const
{
	const auto OnYourOwnGameMode = GetOnYourOwnGameMode();
	return OnYourOwnGameMode ? OnYourOwnGameMode->GetTimeRemaining() : 0;
}

AOnYourOwnGameMode* UTimerWidget::GetOnYourOwnGameMode() const
{
	return GetWorld() ? Cast<AOnYourOwnGameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
}