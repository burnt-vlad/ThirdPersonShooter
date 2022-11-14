// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/Characters/AICharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/AIWeaponComponentTPS.h"
#include "ThirdPersonShooter/Controllers/AIControllerTPS.h"
#include "BehaviorTree/BehaviorTree.h"

AAICharacterTPS::AAICharacterTPS(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponentTPS>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AAIControllerTPS::StaticClass();

	AIViewPoint = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	AIViewPoint->SetupAttachment(GetRootComponent());
}

