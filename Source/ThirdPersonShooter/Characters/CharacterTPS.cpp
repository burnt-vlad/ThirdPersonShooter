// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/PlayerControllers/PlayerControllerTPS.h"
#include "ThirdPersonShooter/ActorComponents/HealthComponentTPS.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "Components/CapsuleComponent.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThirdPersonShooter/GameModes/OnYourOwnGameMode.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "ThirdPersonShooter/ThirdPersonShooter.h"
#include "DrawDebugHelpers.h"

ACharacterTPS::ACharacterTPS(const FObjectInitializer& ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerController = CreateDefaultSubobject<APlayerControllerTPS>("PlayerController");
	HealthComponent = CreateDefaultSubobject<UHealthComponentTPS>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponentTPS>("WeaponComponent");

	CharacterState = ECharacterState::ECS_Unoccupied;
}

void ACharacterTPS::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddUObject(this, &ACharacterTPS::Death);
}

void ACharacterTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterTPS::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ACharacterTPS::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ACharacterTPS::TurnUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ACharacterTPS::TurnRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void ACharacterTPS::Death()
{
	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	GetMesh()->SetSimulatePhysics(true);
	if (WeaponComponent)
	{
		WeaponComponent->DropFirearm(WeaponComponent->GetEquippedFirearmIndex());
		WeaponComponent->ShootButtonReleased();
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FTimerHandle RespawnDelay;
	GetWorldTimerManager().SetTimer(RespawnDelay, this, &ACharacterTPS::CallRespawn, 3.f, false);
}

void ACharacterTPS::CallRespawn()
{
	if (GetController())
	{
		const auto CurrentController = GetController();
		UWorld* World = GetWorld();
		if (World && CurrentController)
		{
			if (AOnYourOwnGameMode* GameMode = Cast<AOnYourOwnGameMode>(World->GetAuthGameMode()))
			{
				GameMode->Respawn(CurrentController);
			}
		}
	}
}

void ACharacterTPS::PlayHipFireMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
	}
}

void ACharacterTPS::PlayReloadMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ReloadMontage)
	{
		const auto EquippedFirearm = WeaponComponent->GetEquippedFirearm();
		if (!EquippedFirearm) return;
		AnimInstance->Montage_Play(ReloadMontage);
		AnimInstance->Montage_JumpToSection(EquippedFirearm->GetReloadMontageSectionName());
	}
}

void ACharacterTPS::PlayEquipMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(FName("EquipStart"));
	}
}

EPhysicalSurface ACharacterTPS::GetSurfaceTypeUnderCharacter()
{
	//Returns the surface type under the character. Depending on the surface, a different sound will be played and different splashes will be spawned
	FHitResult HitResult;
	const FVector TraceStart = GetActorLocation();
	const FVector TraceEnd = TraceStart - FVector(0.f, 0.f, 150.f);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel2, CollisionQueryParams);
	return UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
}
