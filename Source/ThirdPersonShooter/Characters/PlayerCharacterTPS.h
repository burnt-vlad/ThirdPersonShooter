// ThirdPersonShooter/ Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonShooter/Characters/CharacterTPS.h"
#include "PlayerCharacterTPS.generated.h"

class UPlayerWeaponComponentTPS;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class THIRDPERSONSHOOTER_API APlayerCharacterTPS : public ACharacterTPS
{
	GENERATED_BODY()
	
public:
	APlayerCharacterTPS(const FObjectInitializer& ObjInit);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	AFirearmTPS* TraceForFirearm();
	void AimInterp(float DeltaTime);
	FTransform GetCameraTransform() const; 

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float AimInterpSpeed;

	float CameraDefaultFOV;
	float CameraCurrentFOV;

public:

};
