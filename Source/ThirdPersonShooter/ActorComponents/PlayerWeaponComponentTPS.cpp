// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/ActorComponents/PlayerWeaponComponentTPS.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/Characters/PlayerCharacterTPS.h"

void UPlayerWeaponComponentTPS::PickupFirearm()
{
	//Calls the trace function from the player camera, if the trace is successful adds the firearm to the inventory or replaces the main firearm
	const auto Player = Cast<APlayerCharacterTPS>(OwningCharacter);
	if (!Player) return; 
	const auto FirearmToPickup = Player->TraceForFirearm();
	if (FirearmToPickup && FirearmToPickup != EquippedFirearm && FirearmToPickup->GetFirearmState() == EFirearmState::EFS_ReadyToPickup)
	{
		if (FirearmInventory.Contains(nullptr))
		{
			int32 FirearmInventoryEmptySlot;
			EquippedFirearmIndex = (EquippedFirearmIndex + 1) % FirearmInventory.Num();
			FirearmInventory.Find(nullptr, FirearmInventoryEmptySlot);
			FirearmInventory[FirearmInventoryEmptySlot] = FirearmToPickup;
			AttachFirearmToSocket(EquippedFirearm, SecondaryFirearmSocketName);
			EquippedFirearm->SetFirearmState(EFirearmState::EFS_PickedUp);
			EquipFirearm(FirearmInventoryEmptySlot);
		}
		else
		{
			DropFirearm(EquippedFirearmIndex);
			FirearmInventory[EquippedFirearmIndex] = FirearmToPickup;
			EquipFirearm(EquippedFirearmIndex);
		}
	}
}