// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/AI/Services/FireServiceTPS.h"
#include "ThirdPersonShooter/ActorComponents/AIWeaponComponentTPS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFireServiceTPS::UFireServiceTPS()
{
	NodeName = "Fire";
}

void UFireServiceTPS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if (Controller)
	{
		const auto WeaponComponent = Cast<UAIWeaponComponentTPS>(Controller->GetPawn()->GetComponentByClass(UAIWeaponComponentTPS::StaticClass()));
		if (WeaponComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), HasAim ? TEXT("true") : TEXT("false"));
			HasAim ? WeaponComponent->ShootButtonPressed() : WeaponComponent->ShootButtonReleased();
		}
	}
}