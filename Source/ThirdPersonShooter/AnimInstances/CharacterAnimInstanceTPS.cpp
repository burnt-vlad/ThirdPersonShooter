// ThirdPersonShooter/ Fedosov Vladislav


#include "ThirdPersonShooter/AnimInstances/CharacterAnimInstanceTPS.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "ThirdPersonShooter/ActorComponents/WeaponComponentTPS.h"
#include "ThirdPersonShooter/Actors/FirearmTPS.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstanceTPS::NativeInitializeAnimation()
{
	Character = Cast<ACharacterTPS>(TryGetPawnOwner());
	ShouldUseFABRIK = true;
}

void UCharacterAnimInstanceTPS::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	CharacterWeaponComponent = Character->GetWeaponComponent();
	CharacterWeaponComponent->OnEquip.AddUObject(this, &UCharacterAnimInstanceTPS::OnEquip);
	CharacterWeaponComponent->OnReloadStartDelegate.AddUObject(this, &UCharacterAnimInstanceTPS::SetFABRIKfalse);
	CharacterWeaponComponent->OnReloadFinishDelegate.AddUObject(this, &UCharacterAnimInstanceTPS::SetFABRIKtrue);
	CharacterWeaponComponent->OnEquipStartDelegate.AddUObject(this, &UCharacterAnimInstanceTPS::SetFABRIKfalse);
	CharacterWeaponComponent->OnReloadFinishDelegate.AddUObject(this, &UCharacterAnimInstanceTPS::SetFABRIKtrue);
	RootYaw = 0.f;
}

void UCharacterAnimInstanceTPS::OnEquip(EFirearm EquippedFirearm) // Firearm switch delegate for FABRIK hands
{
	Firearm = EquippedFirearm;
}

void UCharacterAnimInstanceTPS::UpdateAnimationProperties(float DeltaTime)
{
	if (!Character) Character = Cast<ACharacterTPS>(TryGetPawnOwner());
	if (Character)
	{
		bIsAiming = Character->bIsAiming();
		FVector Velocity = Character->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();
		bIsInAir = Character->GetCharacterMovement()->IsFalling();
		if (Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
		MovementDirection = GetMovementDirectionYaw();
		if (Character->GetVelocity().Size() > 0.f) LastMovementDirection = MovementDirection;
	}
	TurnInPlace();
}

float UCharacterAnimInstanceTPS::GetMovementDirectionYaw() const
{
	FRotator AimRotation = Character->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());
	return UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
}

void UCharacterAnimInstanceTPS::TurnInPlace()
{
	if (!Character) return;
	Pitch = Character->GetBaseAimRotation().Pitch;
	if (Speed > 0)
	{
		RootYaw = 0;
		CharacterCurrentYaw = Character->GetActorRotation().Yaw;
		CurveRotationLastFrame = CharacterCurrentYaw;
		CurveRotationLastFrame = 0.f;
		CurveRotation = 0.f;
	}
	else
	{
		CharacterLastFrameYaw = CharacterCurrentYaw;
		CharacterCurrentYaw = Character->GetActorRotation().Yaw;
		const float YawDelta = CharacterCurrentYaw - CharacterLastFrameYaw;
		RootYaw = UKismetMathLibrary::NormalizeAxis(RootYaw - YawDelta);

		const float Turning = GetCurveValue(TEXT("Turning"));
		if (Turning > 0)
		{
			CurveRotationLastFrame = CurveRotation;
			CurveRotation = GetCurveValue(TEXT("Rotation"));
			const float DeltaRotation = CurveRotation - CurveRotationLastFrame;
			RootYaw > 0 ? RootYaw -= DeltaRotation : RootYaw += DeltaRotation;
			const float ABSRootYaw = FMath::Abs(RootYaw);
			if (ABSRootYaw > 60.f)
			{
				const float YawExcess = ABSRootYaw - 60.f;
				RootYaw > 0 ? RootYaw -= YawExcess : RootYaw += YawExcess;
			}
		}
	}
}