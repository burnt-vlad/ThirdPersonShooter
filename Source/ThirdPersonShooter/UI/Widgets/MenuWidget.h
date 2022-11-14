// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;

UCLASS()
class THIRDPERSONSHOOTER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartPlayButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnStartGame();

};
