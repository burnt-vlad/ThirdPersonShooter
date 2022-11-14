// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIPerceptionComponentTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UAIPerceptionComponentTPS : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosestEnemy() const;
};
