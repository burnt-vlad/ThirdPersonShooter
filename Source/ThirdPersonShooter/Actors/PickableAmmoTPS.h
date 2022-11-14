// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/Actors/PickableItemTPS.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "PickableAmmoTPS.generated.h"


UCLASS()
class THIRDPERSONSHOOTER_API APickableAmmoTPS : public APickableItemTPS
{
	GENERATED_BODY()
	
public:	
	APickableAmmoTPS();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Properties", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Properties", meta = (AllowPrivateAccess = "true"))
	int32 AmmoCount;

public:
	EAmmoType GetAmmoType() const { return AmmoType; }
	int32 GetAmmoCount() const { return AmmoCount; }

};
