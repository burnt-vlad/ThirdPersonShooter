// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/AI/Services/FindEnemyServiceTPS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPersonShooter/Controllers/AIControllerTPS.h"
#include "ThirdPersonShooter/AI/Components/AIPerceptionComponentTPS.h"

UFindEnemyServiceTPS::UFindEnemyServiceTPS()
{
	NodeName = "Find Enemy";
}

void UFindEnemyServiceTPS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Cast<UAIPerceptionComponentTPS>(Controller->GetComponentByClass(UAIPerceptionComponentTPS::StaticClass()));
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}