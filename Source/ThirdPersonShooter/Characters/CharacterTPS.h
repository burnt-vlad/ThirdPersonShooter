// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonShooter/DataTypes.h"
#include "CharacterTPS.generated.h"

class APlayerControllerTPS;
class UHealthComponentTPS;
class UWeaponComponentTPS;
class AFirearmTPS;

UCLASS()
class THIRDPERSONSHOOTER_API ACharacterTPS : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterTPS(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;

	void PlayHipFireMontage();
	void PlayReloadMontage();
	void PlayEquipMontage();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnUp(float Amount);
	void TurnRight(float Amount);
	void StartAim() { bAiming = true; }
	void EndAim() { bAiming = false; }
	virtual void Death();
	void CallRespawn();
	UFUNCTION(BlueprintCallable)
	EPhysicalSurface GetSurfaceTypeUnderCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponentTPS* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		bool bAiming;

private:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		APlayerControllerTPS* PlayerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UWeaponComponentTPS* WeaponComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* HipFireMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* ReloadMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* EquipMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = "true"))
		ECharacterState CharacterState;

public:
	void SetCharacterState(ECharacterState State) { CharacterState = State; }
	ECharacterState GetCharacterState() const { return CharacterState; }
	UWeaponComponentTPS* GetWeaponComponent() const { return WeaponComponent; }
	UHealthComponentTPS* GetHealthComponent() const { return HealthComponent; }
	bool bIsAiming() const { return bAiming; }

};
