// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyServiceTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UFindEnemyServiceTPS : public UBTService
{
	GENERATED_BODY()

public:
	UFindEnemyServiceTPS();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;
};
