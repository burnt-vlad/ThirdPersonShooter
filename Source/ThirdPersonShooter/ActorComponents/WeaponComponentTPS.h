// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "WeaponComponentTPS.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquip, EFirearm);
DECLARE_MULTICAST_DELEGATE(FOnReloadStart);
DECLARE_MULTICAST_DELEGATE(FOnReloadFinish);
DECLARE_MULTICAST_DELEGATE(FOnEquipStart);
DECLARE_MULTICAST_DELEGATE(FOnEquipFinish);

class ACharacterTPS;
class AFirearmTPS;
class APickableAmmoTPS;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API UWeaponComponentTPS : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponentTPS();
	virtual void ShootButtonPressed();
	virtual void ShootButtonReleased();
	void StartReload();
	void ReduceAmmo(const EAmmoType AmmoType, const int32 AmmoAmount);
	AFirearmTPS* NextFirearm();
	void PickupAmmo(APickableAmmoTPS* Ammo);
	void DropFirearm(int32 FirearmIndex);
	void StartFirearmSwitch();
	bool CanShoot();

	FOnEquip OnEquip;
	FOnReloadStart OnReloadStartDelegate;
	FOnReloadFinish OnReloadFinishDelegate;
	FOnEquipStart OnEquipStartDelegate;
	FOnEquipFinish OnEquipFinishDelegate;

	void OnReloadFinish();
	virtual void PickupFirearm() { ; }

protected:
	virtual void BeginPlay() override;
	void EquipFirearm(int32 FirearmIndex);
	void AttachFirearmToSocket(AFirearmTPS* FirearmToAttach, const FName& SocketName);
	void DetachFirearmFromSocket(AFirearmTPS* FirearmToDetach);

	UFUNCTION(BlueprintCallable)
		void GrabClip();
	UFUNCTION(BlueprintCallable)
		void ReleaseClip();
	UFUNCTION(BlueprintCallable)
		void StopFirearmSwitch();

	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AFirearmTPS> FirearmClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		AFirearmTPS* EquippedFirearm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		TArray<AFirearmTPS*> FirearmInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		int32 EquippedFirearmIndex;
	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		FName SecondaryFirearmSocketName = "SecondaryFirearmSocket";
	ACharacterTPS* OwningCharacter;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		FName RightHandSocketName = "RightHandSocket";
	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		FName LeftHandSocketName = "LeftHandSocket";


	const int32 FirearmInvenoryCapacity = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		TMap<EAmmoType, int32> AmmoInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	int32 StartingAmmo_9mm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	int32 StartingAmmo5_45x39mm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	int32 StartingAmmo7_62x39mm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		FTransform ClipBoneTransform;

	void InitializeFirearmIventory();
	void InitializeAmmoInventory();
	void SpawnDefaultFirearm();
	bool CanReload();

public:
	TMap<EAmmoType, int32> GetAmmoInventory() const { return AmmoInventory; }
	AFirearmTPS* GetEquippedFirearm() const { return EquippedFirearm; }
	TArray<AFirearmTPS*> GetFirearmInventory() const { return FirearmInventory; }
	int32 GetEquippedFirearmIndex() const { return EquippedFirearmIndex; }
};
