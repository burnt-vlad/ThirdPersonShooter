// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "PlayerControllerTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API APlayerControllerTPS : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void PauseGame();
	void OnMatchStateChanged(EMatchState State);

};
