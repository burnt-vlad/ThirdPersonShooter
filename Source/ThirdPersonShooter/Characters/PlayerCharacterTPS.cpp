// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Characters/PlayerCharacterTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "ThirdPersonShooter/ActorComponents/PlayerWeaponComponentTPS.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "DrawDebugHelpers.h"

APlayerCharacterTPS::APlayerCharacterTPS(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UPlayerWeaponComponentTPS>("WeaponComponent"))
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	bAiming = false;
	AimInterpSpeed = 25.f;
}

void APlayerCharacterTPS::BeginPlay()
{
	Super::BeginPlay();
	if (Camera)
	{
		CameraDefaultFOV = Camera->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}
}

void APlayerCharacterTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimInterp(DeltaTime);
}

void APlayerCharacterTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterTPS::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterTPS::MoveRight);
	PlayerInputComponent->BindAxis("TurnUp", this, &APlayerCharacterTPS::TurnUp);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerCharacterTPS::TurnRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, GetWeaponComponent(), &UWeaponComponentTPS::ShootButtonPressed);
	PlayerInputComponent->BindAction("Shoot", IE_Released, GetWeaponComponent(), &UWeaponComponentTPS::ShootButtonReleased);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacterTPS::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacterTPS::EndAim);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, GetWeaponComponent(), &UWeaponComponentTPS::StartReload);
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, GetWeaponComponent(), &UWeaponComponentTPS::PickupFirearm);
	PlayerInputComponent->BindAction("NextFirearm", IE_Pressed, GetWeaponComponent(), &UWeaponComponentTPS::StartFirearmSwitch);
}

AFirearmTPS* APlayerCharacterTPS::TraceForFirearm()
{
	//If the trace was successful, the function returns the firearm in front of the camera
	if (GetCharacterState() == ECharacterState::ECS_Unoccupied)
	{
		if (!Camera) return nullptr;
		FVector TraceStart, TraceEnd;
		FTransform CameraTransform = Camera->GetComponentTransform();
		TraceStart = CameraTransform.GetLocation();
		FVector TraceDirection = CameraTransform.GetRotation().Vector();
		TraceEnd = TraceStart + TraceDirection * 600.f;
		FHitResult CameraTraceHitResult;
		GetWorld()->LineTraceSingleByChannel(CameraTraceHitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 3.f);
		if (CameraTraceHitResult.bBlockingHit)
		{
			const auto TraceHitFirearm = Cast<AFirearmTPS>(CameraTraceHitResult.Actor);
			if (TraceHitFirearm) return TraceHitFirearm;
		}
	}
	return nullptr;
}


void APlayerCharacterTPS::AimInterp(float DeltaTime)
{
	//Reduces FOV when aiming
	if (bAiming)
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV * 0.7f, DeltaTime, AimInterpSpeed);
	}
	else
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, DeltaTime, AimInterpSpeed);
	}
	Camera->SetFieldOfView(CameraCurrentFOV);
}

FTransform APlayerCharacterTPS::GetCameraTransform() const
{
	return Camera ? Camera->GetComponentTransform() : FTransform();
}
