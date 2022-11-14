// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthPercentDecoratorTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UHealthPercentDecoratorTPS : public UBTDecorator
{
	GENERATED_BODY()

public:
	UHealthPercentDecoratorTPS();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float HealthPercent = 0.2f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
