// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "ThirdPersonShooter/Actors/PickableAmmoTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"

UWeaponComponentTPS::UWeaponComponentTPS()
{
	PrimaryComponentTick.bCanEverTick = false;
	StartingAmmo_9mm = 30;
	StartingAmmo5_45x39mm = 30;
	StartingAmmo7_62x39mm = 30;

	EquippedFirearmIndex = 1;
}

void UWeaponComponentTPS::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<ACharacterTPS>(GetOwner());
	InitializeFirearmIventory();
	InitializeAmmoInventory();
	EquipFirearm(EquippedFirearmIndex);
}

void UWeaponComponentTPS::SpawnDefaultFirearm()
{
	if (FirearmClass)
	{
		FirearmInventory.Add(GetWorld()->SpawnActor<AFirearmTPS>(FirearmClass));
	}
}

void UWeaponComponentTPS::AttachFirearmToSocket(AFirearmTPS* FirearmToAttach, const FName& SocketName)
{
	if (FirearmToAttach)
	{
		if (OwningCharacter)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			FirearmToAttach->AttachToComponent(OwningCharacter->GetMesh(), AttachmentRules, SocketName);
		}
	}
}

void UWeaponComponentTPS::DetachFirearmFromSocket(AFirearmTPS* FirearmToDetach)
{
	if (FirearmToDetach)
	{
		if (OwningCharacter)
		{
			FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
			FirearmToDetach->GetFirearmMesh()->DetachFromComponent(DetachmentRules);
		}
	}
}

void UWeaponComponentTPS::ShootButtonPressed()
{
	if(CanShoot())
	{
		OwningCharacter->SetCharacterState(ECharacterState::ECS_Shooting);
		EquippedFirearm->StartFire();
	}
}

void UWeaponComponentTPS::ShootButtonReleased()
{
	if (EquippedFirearm)
	{
		EquippedFirearm->StopFire();
		OwningCharacter->SetCharacterState(ECharacterState::ECS_Unoccupied);
	}
}

bool UWeaponComponentTPS::CanReload()
{
	//Checks all conditions for reloading
	if (EquippedFirearm &&
		OwningCharacter->GetCharacterState() == ECharacterState::ECS_Unoccupied &&
		EquippedFirearm->GetFirearmAmmo() < EquippedFirearm->GetMagazineCapacity() &&
		*AmmoInventory.Find(EquippedFirearm->GetAmmoType()) > 0) return true;
	return false;
}

void UWeaponComponentTPS::StartReload()
{
	if (CanReload())
	{
		OwningCharacter->SetCharacterState(ECharacterState::ECS_Reloading);
		OwningCharacter->PlayReloadMontage();
		OnReloadStartDelegate.Broadcast();
	}
}

void UWeaponComponentTPS::OnReloadFinish()
{
	OwningCharacter->SetCharacterState(ECharacterState::ECS_Unoccupied);
	OnReloadFinishDelegate.Broadcast();
}

void UWeaponComponentTPS::GrabClip()
{
	if (EquippedFirearm)
	{
		int32 ClipBoneIndex = EquippedFirearm->GetFirearmMesh()->GetBoneIndex(EquippedFirearm->GetMagazineBoneName());
		ClipBoneTransform = EquippedFirearm->GetFirearmMesh()->GetBoneTransform(ClipBoneIndex);
		EquippedFirearm->SetMovingClip(true);
	}
}

void UWeaponComponentTPS::ReleaseClip()
{
	if (EquippedFirearm)
	{ 
		EquippedFirearm->SetMovingClip(false);
	}
}

void UWeaponComponentTPS::InitializeFirearmIventory()
{
	FirearmInventory.SetNum(FirearmInvenoryCapacity);
	SpawnDefaultFirearm();
}

void UWeaponComponentTPS::InitializeAmmoInventory()
{
	AmmoInventory.Add(EAmmoType::EAT_Ammo_9mm, StartingAmmo_9mm);
	AmmoInventory.Add(EAmmoType::EAT_Ammo5_45x39mm, StartingAmmo5_45x39mm);
	AmmoInventory.Add(EAmmoType::EAT_Ammo7_62x39mm, StartingAmmo7_62x39mm);
}

void UWeaponComponentTPS::ReduceAmmo(const EAmmoType AmmoType, const int32 AmmoAmount)
{
	if (AmmoInventory.Find(AmmoType) > 0)
	{
		*AmmoInventory.Find(AmmoType) -= AmmoAmount;
	}
}

void UWeaponComponentTPS::EquipFirearm(int32 FirearmIndex)
{
	EquippedFirearm = FirearmInventory[FirearmIndex];
	OnEquip.Broadcast(EquippedFirearm->GetFirearm());
	EquippedFirearm->SetFirearmState(EFirearmState::EFS_Equipped);
	EquippedFirearm->SetOwner(GetOwner());
	AttachFirearmToSocket(EquippedFirearm, RightHandSocketName); 
}

void UWeaponComponentTPS::DropFirearm(int32 FirearmIndex)
{
	DetachFirearmFromSocket(FirearmInventory[FirearmIndex]);
	FirearmInventory[FirearmIndex]->SetFirearmState(EFirearmState::EFS_ReadyToPickup);
	FirearmInventory[FirearmIndex]->SetOwner(nullptr);
	FirearmInventory[FirearmIndex] = nullptr;
}

AFirearmTPS* UWeaponComponentTPS::NextFirearm()
{
	//Returns a firearm from the next element of the FirearmInventory
	EquippedFirearmIndex = (EquippedFirearmIndex + 1) % FirearmInventory.Num();
	if (!FirearmInventory[EquippedFirearmIndex]) return nullptr;
	return FirearmInventory[EquippedFirearmIndex];
}

void UWeaponComponentTPS::StartFirearmSwitch()
{
	if (OwningCharacter->GetCharacterState() == ECharacterState::ECS_Unoccupied)
	{
		if (!FirearmInventory[(EquippedFirearmIndex + 1) % FirearmInventory.Num()]) return;
		OnEquipStartDelegate.Broadcast();
		OwningCharacter->SetCharacterState(ECharacterState::ECS_Equipping);
		OwningCharacter->PlayEquipMontage();
	}
}

void UWeaponComponentTPS::StopFirearmSwitch()
{
	//Called at the end of the reload animation via an anim notify
	AttachFirearmToSocket(EquippedFirearm, SecondaryFirearmSocketName);
	EquippedFirearm->SetFirearmState(EFirearmState::EFS_PickedUp);
	EquippedFirearm = NextFirearm();
	EquipFirearm(EquippedFirearmIndex);
	OnEquipFinishDelegate.Broadcast();
	OwningCharacter->SetCharacterState(ECharacterState::ECS_Unoccupied);
}

bool UWeaponComponentTPS::CanShoot()
{
	//Checks all conditions for shooting
	if (EquippedFirearm &&
		OwningCharacter->GetCharacterState() == ECharacterState::ECS_Unoccupied && 
		EquippedFirearm->GetFirearmState() == EFirearmState::EFS_Equipped &&
		!EquippedFirearm->bIsFirearmEmpty()) return true;
	return false;
}

void UWeaponComponentTPS::PickupAmmo(APickableAmmoTPS* Ammo)
{
	if (AmmoInventory.Find(Ammo->GetAmmoType()) && Ammo)
	{
		int32 AmmoInventoryCount = AmmoInventory[Ammo->GetAmmoType()];
		AmmoInventoryCount += Ammo->GetAmmoCount();
		AmmoInventory[Ammo->GetAmmoType()] = AmmoInventoryCount;
	}
}

