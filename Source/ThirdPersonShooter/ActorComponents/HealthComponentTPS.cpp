// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"
#include "ThirdPersonShooter/Actors/PickableHealthTPS.h"

UHealthComponentTPS::UHealthComponentTPS()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.f;

}

void UHealthComponentTPS::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponentTPS::OnTakeAnyDamage);
	}
}

void UHealthComponentTPS::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	if (IsDead()) OnDeath.Broadcast();
}

void UHealthComponentTPS::AddHealth(float Amount)
{
	if (GetHealth() >= MaxHealth) return;
	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);
}

