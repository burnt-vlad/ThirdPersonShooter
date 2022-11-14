// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/Controllers/AIControllerTPS.h"
#include "ThirdPersonShooter/Characters/AICharacterTPS.h"
#include "ThirdPersonShooter/AI/Components/AIPerceptionComponentTPS.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"
#include "BrainComponent.h"

AAIControllerTPS::AAIControllerTPS()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponentTPS>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
	bWantsPlayerState = true;
}

void AAIControllerTPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacterTPS = Cast<AAICharacterTPS>(InPawn);
	if (AICharacterTPS)
	{
		RunBehaviorTree(AICharacterTPS->GetBehaviorTreeAsset());
		AICharacterTPS->GetHealthComponent()->OnDeath.AddUObject(this, &AAIControllerTPS::StopBrainLogic);
	}
}

void AAIControllerTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

void AAIControllerTPS::StopBrainLogic()
{
	BrainComponent->StopLogic(TEXT(""));
}

AActor* AAIControllerTPS::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
