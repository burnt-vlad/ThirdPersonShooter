// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponentTPS.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

class APickableHealthTPS;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API UHealthComponentTPS : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponentTPS();
	FOnDeath OnDeath;
	void AddHealth(float Amount);
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.0f; }
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const {return Health / MaxHealth;}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float MaxHealth;

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	float GetHealth() const { return Health; }

};
