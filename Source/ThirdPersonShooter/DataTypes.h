#pragma once

#include "DataTypes.generated.h"

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	EAT_Ammo_9mm UMETA(DisplayName = "9mm"),
	EAT_Ammo5_45x39mm UMETA(DisplayName = "5,45x39mm"),
	EAT_Ammo7_62x39mm UMETA(DisplayName = "7,62x39mm")
};

UENUM(BlueprintType)
enum class EFirearmState : uint8
{
	EFS_ReadyToPickup UMETA(DisplayName = "ReadyToPickup"),
	EFS_PickedUp UMETA(DisplayName = "ReadyToPickup"),
	EFS_Equipped UMETA(DisplayName = "Equipped")
};

UENUM(BlueprintType)
enum class EFirearm : uint8
{
	EWT_ASVAL UMETA(DisplayName = "AS VAL"),
	EWT_AR4 UMETA(DisplayName = "AR4"),
	EWT_AKM UMETA(DisplayName = "AKM")
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_Equipping UMETA(DisplayName = "Equipping"),
	ECS_Shooting UMETA(DisplayName = "Shooting"),
	ECS_Reloading UMETA(DisplayName = "Reloading")
};

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	EMS_WaitingForTheStart UMETA(DisplayName = "Waiting for the start"),
	EMS_GameInProgress UMETA(DisplayName = "Game In Progress"),
	EMS_OnPause UMETA(DisplayName = "On Pause"),
	EMS_GameOver UMETA(DisplayName = "Game Over")
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, EMatchState);