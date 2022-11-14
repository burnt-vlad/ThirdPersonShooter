// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/Actors/PickableItemTPS.h"
#include "PickableHealthTPS.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API APickableHealthTPS : public APickableItemTPS
{
	GENERATED_BODY()
public:
	APickableHealthTPS();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Pickup Properties", meta = (AllowPrivateAccess = "true"))
		float HealthPickupAmount;

};
