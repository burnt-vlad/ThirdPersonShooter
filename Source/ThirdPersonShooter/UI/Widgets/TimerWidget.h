// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

class AOnYourOwnGameMode;

UCLASS()
class THIRDPERSONSHOOTER_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
		int32 GetTimeRemaining() const;

private:
	AOnYourOwnGameMode* GetOnYourOwnGameMode() const;
};
