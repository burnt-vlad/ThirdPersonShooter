// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONSHOOTER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* RestartButton;

	UFUNCTION()
		void OnResetLevel();

};
