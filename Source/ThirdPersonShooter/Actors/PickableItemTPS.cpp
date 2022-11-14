// ThirdPersonShooter/ Fedosov Vladislav

#include "ThirdPersonShooter/Actors/PickableItemTPS.h"
#include "Components/SphereComponent.h"
#include "ThirdPersonShooter/ActorComponents/ItemRotatingComponentTPS.h"
#include "Components/PointLightComponent.h"

APickableItemTPS::APickableItemTPS()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	ItemSphereCollision = CreateDefaultSubobject<USphereComponent>("ItemSphereCollision");
	ItemSphereCollision->SetupAttachment(GetRootComponent());
	ItemSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ItemSphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	PointLight->SetupAttachment(ItemMesh);
	PointLight->Intensity = 2500.f;
	PointLight->CastShadows = false;

	ItemRotatingComponent = CreateDefaultSubobject<UItemRotatingComponentTPS>("ItemRotatingComponent");

	ActivationDelay = 10.f;
}

void APickableItemTPS::BeginPlay()
{
	Super::BeginPlay();
	ItemSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickableItemTPS::OnItemSphereOverlap);
	InitialAmmoLocation = ItemMesh->GetRelativeLocation();
}

void APickableItemTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector CurrentAmmoLocation = GetActorLocation();
	//float Time = GetWorld()->GetTimeSeconds();
	//CurrentAmmoLocation.Z = (InitialAmmoLocation.Z + 20.f * FMath::Sin(2.f * Time));
	//SetActorLocation(CurrentAmmoLocation);
	//FRotator CurrentAmmoRotation = GetActorRotation();
	//CurrentAmmoRotation.Yaw += 1.f;
	//float F = FMath::FInterpTo(CurrentAmmoRotation.Yaw, DeltaTime, 360, 1.f);
	//SetActorRotation(CurrentAmmoRotation);
}


void APickableItemTPS::OnItemSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Deactivate();
	}
}

void APickableItemTPS::Activate()
{
	if (ItemMesh)
	{
		ItemSphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		ItemMesh->SetVisibility(true);
		PointLight->SetVisibility(true);
	}
}

void APickableItemTPS::Deactivate()
{
	if (ItemMesh)
	{
		ItemSphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMesh->SetVisibility(false);
		PointLight->SetVisibility(false);
		FTimerHandle ActivationTimer;
		GetWorldTimerManager().SetTimer(ActivationTimer, this, &APickableItemTPS::Activate, ActivationDelay, false);
	}
}


