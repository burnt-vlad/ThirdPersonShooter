// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Actors/PickableHealthTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"

APickableHealthTPS::APickableHealthTPS()
{
	HealthPickupAmount = 35.f;
}

void APickableHealthTPS::BeginPlay()
{
	Super::BeginPlay();
}

void APickableHealthTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickableHealthTPS::OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnItemSphereOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		const auto OverlappedCharacter = Cast<ACharacterTPS>(OtherActor);
		if (!OverlappedCharacter) return;
		const auto CharacterHealthComponent = OverlappedCharacter->GetHealthComponent();
		if (!CharacterHealthComponent) return;
		CharacterHealthComponent->AddHealth(HealthPickupAmount);
	}
}