// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "AIWeaponComponentTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UAIWeaponComponentTPS : public UWeaponComponentTPS
{
	GENERATED_BODY()
public:
	virtual void ShootButtonPressed() override;

};
