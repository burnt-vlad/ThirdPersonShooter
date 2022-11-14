// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "Engine/DataTable.h"
#include "FirearmTPS.generated.h"

class UBoxComponent;
class UWeaponComponentTPS;
class USoundCue;
class UParticleSystem;

USTRUCT(BlueprintType)
struct FFirearmDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFirearm Firearm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName FirearmName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* FirearmMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName MagazineBoneName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName MuzzleSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ReloadMontageSectionName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAmmoType AmmoType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 FirearmAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MagazineCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FiringRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  bAutomatic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* ShotSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* FirearmIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HeadShotDamage;
};

UCLASS()
class THIRDPERSONSHOOTER_API AFirearmTPS : public AActor
{
	GENERATED_BODY()

public:
	AFirearmTPS();
	void StartFire();
	void StopFire();
	UFUNCTION(BlueprintCallable)
		void FinishReload();
	void SetFirearmState(EFirearmState State);
	bool bIsFirearmEmpty();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		UDataTable* FirearmDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* FirearmMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* FirearmCollisionBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		EFirearm Firearm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		FName FirearmName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		FName MagazineBoneName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		FName MuzzleSocketName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		FName ReloadMontageSectionName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		EAmmoType AmmoType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		int32 FirearmAmmo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		int32 MagazineCapacity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		float FiringRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		bool  bAutomatic;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		float FireRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		UParticleSystem* MuzzleFlash;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		USoundCue* ShotSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		UTexture2D* FirearmIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		float Damage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		float HeadShotDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		bool bMovingClip;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		bool bCanShoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
		EFirearmState FirearmState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firearm Properties", meta = (AllowPrivateAccess = "true"))
	FTimerHandle FireDelayTimer;

	void FireDelayTimerStart();

	bool GetOwningCharacterViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	bool GetFirearmMuzzleSocketTransform(FTransform& TraceStartTransform);
	bool GetViewTraceEnd(FVector& TraceEnd);
	void MakeTraceHit(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd);
	void MakeDamage(const FHitResult& HitResult);

	void FireDelayTimerReset();
	void MakeShot();
	void PlayShotSound();
	void SpawnMuzzleFlash();

	void ReduceAmmo();
	bool FirearmHasAmmo();
	bool CanReload();
	UWeaponComponentTPS* GetWeaponComponent();

public:
	USkeletalMeshComponent* GetFirearmMesh() const { return FirearmMesh; }
	EFirearmState GetFirearmState() const { return FirearmState; }
	EFirearm GetFirearm() const { return Firearm; }
	EAmmoType GetAmmoType() const { return AmmoType; }
	int32 GetMagazineCapacity() const { return MagazineCapacity; }
	int32 GetFirearmAmmo() const { return FirearmAmmo; }
	FName GetReloadMontageSectionName() const { return ReloadMontageSectionName; }
	FName GetMagazineBoneName() const { return MagazineBoneName; }
	void SetMovingClip(bool Move) { bMovingClip = Move; }
};
