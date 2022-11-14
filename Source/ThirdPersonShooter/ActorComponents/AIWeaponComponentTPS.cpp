// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/ActorComponents/AIWeaponComponentTPS.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"

void UAIWeaponComponentTPS::ShootButtonPressed()
{
	if (EquippedFirearm->bIsFirearmEmpty() && OwningCharacter->GetCharacterState() == ECharacterState::ECS_Unoccupied)
	{
		ShootButtonReleased();
		StartReload();
	}
	else
	{
		if (!CanShoot()) return;
		EquippedFirearm->StartFire();
	}
}
