// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "CharacterAnimInstanceTPS.generated.h"

class ACharacterTPS;
class UWeaponComponentTPS;

UCLASS()
class THIRDPERSONSHOOTER_API UCharacterAnimInstanceTPS : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
	virtual void NativeInitializeAnimation() override;
	float GetMovementDirectionYaw() const;

protected:
	void TurnInPlace();
	virtual void NativeBeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		ACharacterTPS* Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		UWeaponComponentTPS* CharacterWeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		bool bIsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MovementDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float LastMovementDirection;

	float CharacterCurrentYaw;
	float CharacterLastFrameYaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RootYaw;

	float CurveRotation;
	float CurveRotationLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		bool ShouldUseFABRIK;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		bool bIsAiming;


	void OnEquip(EFirearm EquippedFirearm);
	void OnReloadStart() { ShouldUseFABRIK = false; }
	void OnReloadFinish() { ShouldUseFABRIK = true; }
	void SetFABRIKtrue() { ShouldUseFABRIK = true; }
	void SetFABRIKfalse() { ShouldUseFABRIK = false; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		EFirearm Firearm;
};
