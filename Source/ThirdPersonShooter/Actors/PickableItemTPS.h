// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItemTPS.generated.h"

class USphereComponent;
class UItemRotatingComponentTPS;
class UPointLightComponent;

UCLASS()
class THIRDPERSONSHOOTER_API APickableItemTPS : public AActor
{
	GENERATED_BODY()
	
public:	
	APickableItemTPS();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
		UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
		USphereComponent* ItemSphereCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
		UItemRotatingComponentTPS* ItemRotatingComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
		UPointLightComponent* PointLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
		float ActivationDelay;
	FVector InitialAmmoLocation;
	
	void Activate();
	void Deactivate();
	UFUNCTION() 
		virtual void OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
