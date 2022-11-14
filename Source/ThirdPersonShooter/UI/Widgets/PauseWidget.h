// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONSHOOTER_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget))
		UButton* RestartButton;

	UFUNCTION()
		void OnResume();
	UFUNCTION()
		void OnResetLevel();

};
