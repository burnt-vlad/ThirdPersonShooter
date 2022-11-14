// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FireServiceTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UFireServiceTPS : public UBTService
{
	GENERATED_BODY()

public:
	UFireServiceTPS();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;
};
