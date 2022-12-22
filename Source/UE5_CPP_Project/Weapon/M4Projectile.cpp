#include "Weapon/M4Projectile.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy/BaseZombie.h"
#include "Engine/EngineTypes.h"
AM4Projectile::AM4Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &SphereCollision, "SphereCollision", GetRootComponent());
	CHelpers::CreateComponent(this, &Mesh, "Mesh", SphereCollision);

	UStaticMesh* mesh;

	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Player/Weapon/Bullet/bullet_High.Bullet_High'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeLocation(FVector(-12.941294f, 0.000118f, 0.893866f));
	Mesh->SetRelativeRotation(FRotator(-90.0f, 180.0f, 180.0f));
	Mesh->SetRelativeScale3D(FVector(7.0f, 7.0f, 7.0f));
}

void AM4Projectile::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentHit.AddDynamic(this, &AM4Projectile::OnHit);

	
}

void AM4Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AM4Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	CheckNull(OtherActor);
	ABaseZombie* Zombie = Cast<ABaseZombie>(OtherActor);
	CheckNull(Zombie);
	FDamageEvent e;
	Zombie->TakeDamage(10.0f, e, UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	Destroy();
}

