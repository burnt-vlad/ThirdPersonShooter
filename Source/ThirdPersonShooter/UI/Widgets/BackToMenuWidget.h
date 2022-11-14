// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BackToMenuWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONSHOOTER_API UBackToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BackToMainMenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnBackToMainMenu();
};
