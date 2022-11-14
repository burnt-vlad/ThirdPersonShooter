// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/Characters/PlayerCharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AFirearmTPS::AFirearmTPS()
{
	PrimaryActorTick.bCanEverTick = false;
	FirearmMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FirearmMesh");
	SetRootComponent(FirearmMesh);
	FirearmCollisionBox = CreateDefaultSubobject<UBoxComponent>("FirearmCollisionBox");
	FirearmCollisionBox->SetupAttachment(GetRootComponent());
	bCanShoot = true;
	FirearmState = EFirearmState::EFS_ReadyToPickup;
}

void AFirearmTPS::BeginPlay()
{
	Super::BeginPlay();
}

void AFirearmTPS::StartFire()
{
	ACharacterTPS* OwningCharacter = Cast<ACharacterTPS>(GetOwner());
	if (!OwningCharacter) return;
	if (FirearmHasAmmo() && bCanShoot)
	{
		MakeShot();
		PlayShotSound();
		SpawnMuzzleFlash();
		OwningCharacter->PlayHipFireMontage();
		GetWorldTimerManager().SetTimer(FireDelayTimer, this, &AFirearmTPS::FireDelayTimerStart, FireRate);
	}
}

void AFirearmTPS::FireDelayTimerStart()
{
	bAutomatic ? StartFire() : StopFire();
}

void AFirearmTPS::StopFire()
{
	bCanShoot = false;
	//Checking the timer to keep the firing rate and avoid instant clearing the timer when releasing the button
	if (GetWorldTimerManager().IsTimerActive(FireDelayTimer))
	{
		FTimerHandle ClearFireTimerDelay;
		float DelayRemaining = GetWorldTimerManager().GetTimerRemaining(FireDelayTimer);
		GetWorldTimerManager().SetTimer(ClearFireTimerDelay, this, &AFirearmTPS::FireDelayTimerReset, DelayRemaining);
	}
	else
	{
		FireDelayTimerReset();
	}
}

void AFirearmTPS::FireDelayTimerReset()
{
	bCanShoot = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimer);
}

void AFirearmTPS::MakeShot()
{
	//Creating two logical traces. The first from the "eyes" of the character and the second from the muzzle of the weapon.
	FHitResult FirearmHitResult;
	FTransform FirearmTraceStartTransform;
	FVector FirearmTraceStart, FirearmTraceEnd, ViewTraceEnd, Direction;
	//Getting firearm trace start point. Getting view end point to calculate direction and end point of shooting
	//Two traces are needed to avoid shooting when the character is behind the wall
	if (GetFirearmMuzzleSocketTransform(FirearmTraceStartTransform) == false || GetViewTraceEnd(ViewTraceEnd) == false) return;
	FirearmTraceStart = FirearmTraceStartTransform.GetLocation();
	Direction = ViewTraceEnd - FirearmTraceStart;
	FirearmTraceEnd = Direction * FiringRange;
	MakeTraceHit(FirearmHitResult, FirearmTraceStart, FirearmTraceEnd);
	if (FirearmHitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), FirearmTraceStart, FirearmHitResult.ImpactPoint, FColor::Red, false, 0.5f, 0, 1.f);
		DrawDebugSphere(GetWorld(), FirearmHitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 0.5f);
		MakeDamage(FirearmHitResult);
	}
	ReduceAmmo();
}

bool AFirearmTPS::GetOwningCharacterViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto OwningCharacter = Cast<ACharacterTPS>(GetOwner());
	if (!OwningCharacter) return false;

	if (OwningCharacter->IsPlayerControlled())
	{
		//Get player point of view
		const auto Player = Cast<APlayerCharacterTPS>(OwningCharacter);
		if (!Player) return false;
		FTransform CameraTransform = Player->GetCameraTransform();
		ViewLocation = CameraTransform.GetLocation();
		ViewRotation = CameraTransform.GetRotation().Rotator();
		return true;
	}
	else
	{
		//Get bot point of view
		OwningCharacter->GetActorEyesViewPoint(ViewLocation, ViewRotation);
		return true;
	}
	return false;
}

bool AFirearmTPS::GetFirearmMuzzleSocketTransform(FTransform& TraceStartTransform)
{
	if (!FirearmMesh) return false;
	TraceStartTransform = FirearmMesh->GetSocketTransform(MuzzleSocketName);
	return true;
}

bool AFirearmTPS::GetViewTraceEnd(FVector& TraceEnd)
{
	//Returns the point in space where the "eyes" of the character are directed (At a distance of 50,000 points)
	FHitResult EyesHitResult;
	FVector EyesTraceStart, TraceDirection, EyesTraceEnd;
	FRotator ViewRotation;
	if (!GetOwningCharacterViewPoint(EyesTraceStart, ViewRotation)) return false; 
	TraceDirection = ViewRotation.Vector();
	EyesTraceEnd = EyesTraceStart + TraceDirection * 50000.f;
	MakeTraceHit(EyesHitResult, EyesTraceStart, EyesTraceEnd);
	if (EyesHitResult.bBlockingHit)
	{
		TraceEnd = EyesHitResult.Location;
		return true;
	}
	return false;
}

void AFirearmTPS::MakeTraceHit(FHitResult& HitResult, const FVector TraceStart, const FVector TraceEnd)
{
	if (!GetWorld()) return;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void AFirearmTPS::ReduceAmmo()
{
	if (FirearmAmmo <= 0) FirearmAmmo = 0;
	else if (FirearmAmmo > 0) --FirearmAmmo;
}

bool AFirearmTPS::FirearmHasAmmo()
{
	return FirearmAmmo > 0 ? true : false;
}

bool AFirearmTPS::CanReload()
{
	const auto OwningCharacterWeaponComponent = GetWeaponComponent();
	if (!OwningCharacterWeaponComponent) return false;
	auto PlayerAmmoInventory = OwningCharacterWeaponComponent->GetAmmoInventory();
	if (FirearmAmmo < MagazineCapacity && PlayerAmmoInventory.Contains(AmmoType) && *PlayerAmmoInventory.Find(AmmoType) > 0) return true;
	return false;
}

void AFirearmTPS::FinishReload()
{
	const auto OwningPlayerWeaponComponent = GetWeaponComponent();
	if (!OwningPlayerWeaponComponent) return;
	auto PlayerAmmoInventory = OwningPlayerWeaponComponent->GetAmmoInventory();
	const auto OwningCharacter = Cast<ACharacterTPS>(GetOwner());
	if (OwningCharacter)
	{
		OwningPlayerWeaponComponent->OnReloadFinish();
		int32 InventoryAmmo = *PlayerAmmoInventory.Find(AmmoType);
		int32 MagazineEmptySpace = MagazineCapacity - FirearmAmmo;
		if (MagazineEmptySpace >= InventoryAmmo)
		{
			OwningPlayerWeaponComponent->ReduceAmmo(AmmoType, *PlayerAmmoInventory.Find(AmmoType));
			FirearmAmmo += InventoryAmmo;
		}
		else
		{
			OwningPlayerWeaponComponent->ReduceAmmo(AmmoType, MagazineEmptySpace);
			FirearmAmmo += MagazineEmptySpace;
		}
		OwningCharacter->SetCharacterState(ECharacterState::ECS_Unoccupied);
	}
}

void AFirearmTPS::SetFirearmState(EFirearmState State)
{
	switch (State)
	{
	case EFirearmState::EFS_ReadyToPickup:
		FirearmMesh->SetSimulatePhysics(true);
		FirearmMesh->SetEnableGravity(true);
		FirearmMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		FirearmMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

		FirearmCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmCollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		FirearmCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		FirearmState = EFirearmState::EFS_ReadyToPickup;
		break;

	case EFirearmState::EFS_PickedUp:
		FirearmMesh->SetSimulatePhysics(false);
		FirearmMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FirearmCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FirearmState = EFirearmState::EFS_PickedUp;
		break;

	case EFirearmState::EFS_Equipped:
		FirearmMesh->SetSimulatePhysics(false);
		FirearmMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FirearmCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		FirearmCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FirearmState = EFirearmState::EFS_Equipped;
		break;
	default:
		break;
	}
}

bool AFirearmTPS::bIsFirearmEmpty()
{
	return (FirearmAmmo > 0) ? false : true;
}

UWeaponComponentTPS* AFirearmTPS::GetWeaponComponent()
{
	const auto OwningCharacter = Cast<ACharacterTPS>(GetOwner());
	if (!OwningCharacter) return nullptr;
	const auto PlayerWeaponComponent = OwningCharacter->GetWeaponComponent();
	if (!PlayerWeaponComponent) return nullptr;
	return PlayerWeaponComponent;
}

void AFirearmTPS::PlayShotSound()
{
	if (ShotSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ShotSound);
	}
}

void AFirearmTPS::SpawnMuzzleFlash()
{
	if (MuzzleFlash)
	{
		FTransform MuzzleSocketTransform;
		if (GetFirearmMuzzleSocketTransform(MuzzleSocketTransform))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, MuzzleSocketTransform);
		}
	}
}

void AFirearmTPS::OnConstruction(const FTransform& Transform)
{
	const FString FirearmTablePath = TEXT("DataTable'/Game/DataTables/DT_Firearm.DT_Firearm'");
	UDataTable* FirearmTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *FirearmTablePath));
	if (FirearmTableObject)
	{
		FFirearmDataTable* FirearmDataRow = nullptr;
		switch (Firearm)
		{
		case EFirearm::EWT_ASVAL:
			FirearmDataRow = FirearmTableObject->FindRow<FFirearmDataTable>(FName("AS_VAL"), TEXT(""));
			break;
		case EFirearm::EWT_AR4:
			FirearmDataRow = FirearmTableObject->FindRow<FFirearmDataTable>(FName("AR4"), TEXT(""));
			break;
		case EFirearm::EWT_AKM:
			FirearmDataRow = FirearmTableObject->FindRow<FFirearmDataTable>(FName("AKM"), TEXT(""));
			break;
		default:
			break;
		}
		if (FirearmDataRow)
		{
			Firearm = FirearmDataRow->Firearm;
			FirearmName = FirearmDataRow->FirearmName;
			FirearmMesh->SetSkeletalMesh(FirearmDataRow->FirearmMesh);
			MagazineBoneName = FirearmDataRow->MagazineBoneName;
			MuzzleSocketName = FirearmDataRow->MuzzleSocketName;
			ReloadMontageSectionName = FirearmDataRow->ReloadMontageSectionName;
			AmmoType = FirearmDataRow->AmmoType;
			FirearmAmmo = FirearmDataRow->FirearmAmmo;
			MagazineCapacity = FirearmDataRow->MagazineCapacity;
			FiringRange = FirearmDataRow->FiringRange;
			bAutomatic = FirearmDataRow->bAutomatic;
			FireRate = FirearmDataRow->FireRate;
			MuzzleFlash = FirearmDataRow->MuzzleFlash;
			ShotSound = FirearmDataRow->ShotSound;
			FirearmIcon = FirearmDataRow->FirearmIcon;
			Damage = FirearmDataRow->Damage;
			HeadShotDamage = FirearmDataRow->HeadShotDamage;
		}
	}
}

void AFirearmTPS::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	const auto DamagedCharacter = Cast<ACharacter>(DamagedActor);
	if (DamagedCharacter)
	{
		UGameplayStatics::ApplyDamage(DamagedCharacter, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());
	}
}
