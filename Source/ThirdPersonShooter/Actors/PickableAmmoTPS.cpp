// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Actors/PickableAmmoTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"

APickableAmmoTPS::APickableAmmoTPS()
{
	PrimaryActorTick.bCanEverTick = true;

	AmmoType = EAmmoType::EAT_Ammo_9mm;
	AmmoCount = 0;
}

void APickableAmmoTPS::BeginPlay()
{
	Super::BeginPlay();
}

void APickableAmmoTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickableAmmoTPS::OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnItemSphereOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		const auto OverlappedCharacter = Cast<ACharacterTPS>(OtherActor);
		if (!OverlappedCharacter) return;
		const auto CharacterWeaponComponent = OverlappedCharacter->GetWeaponComponent();
		if (!CharacterWeaponComponent) return;
		CharacterWeaponComponent->PickupAmmo(this);
	}
}


