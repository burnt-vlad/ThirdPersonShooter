// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "PlayerWeaponComponentTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UPlayerWeaponComponentTPS : public UWeaponComponentTPS
{
	GENERATED_BODY()
public:

protected:

private:
	virtual void PickupFirearm() override;

public:
};
