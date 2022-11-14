// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerTPS.generated.h"

class UAIPerceptionComponentTPS;

UCLASS()
class THIRDPERSONSHOOTER_API AAIControllerTPS : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerTPS();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		FName FocusOnKeyName = "EnemyActor";

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UAIPerceptionComponentTPS* AIPerceptionComponent;
	void StopBrainLogic();
	AActor* GetFocusOnActor() const;

public:
	UAIPerceptionComponentTPS* GetAIPerceptionComponent() const { return AIPerceptionComponent; }

};
