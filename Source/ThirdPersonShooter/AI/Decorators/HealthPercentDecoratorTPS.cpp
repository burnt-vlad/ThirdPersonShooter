// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/AI/Decorators/HealthPercentDecoratorTPS.h"
#include "AIController.h"
#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"

UHealthPercentDecoratorTPS::UHealthPercentDecoratorTPS()
{
	NodeName = "HealthPercent";
}

bool UHealthPercentDecoratorTPS::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = Cast<UHealthComponentTPS>(Controller->GetPawn()->GetComponentByClass(UHealthComponentTPS::StaticClass()));
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
