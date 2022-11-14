// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/AI/Components/AIPerceptionComponentTPS.h"
#include "ThirdPersonShooter/Controllers/AIControllerTPS.h"
#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"
#include "Perception/AISense_Sight.h"

AActor* UAIPerceptionComponentTPS::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PerciveActor : PercieveActors)
	{
		const auto HealthComponent = Cast<UHealthComponentTPS>(PerciveActor->GetComponentByClass(UHealthComponentTPS::StaticClass()));
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PerciveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerciveActor;
			}
		}
	}
	return BestPawn;
}