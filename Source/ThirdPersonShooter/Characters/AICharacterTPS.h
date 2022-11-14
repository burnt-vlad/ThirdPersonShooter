// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "AICharacterTPS.generated.h"

class UBehaviorTree;

UCLASS()
class THIRDPERSONSHOOTER_API AAICharacterTPS : public ACharacterTPS
{
	GENERATED_BODY()

public:
	AAICharacterTPS(const FObjectInitializer& ObjInit);

protected:

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* BehaviorTreeAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		USceneComponent* AIViewPoint;

public:
	UBehaviorTree* GetBehaviorTreeAsset() const { return BehaviorTreeAsset; }
};
