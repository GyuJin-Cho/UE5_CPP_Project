#include "Weapon/M4Projectile.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy/BaseZombie.h"
#include "Engine/EngineTypes.h"

/**생성자를 통해 CDO를 만들고 Component 및 Mesh인 총알 장착*/
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

/**게임 시작시 OnHit함수를 이벤트 바인딩*/
void AM4Projectile::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentHit.AddDynamic(this, &AM4Projectile::OnHit);
	
}

void AM4Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**총알이 생성되어 좀비에게 맞을경우 데미지를 준다.*/
/**다만 좀비의 BoneName이 Head_M 즉 머리를 맞출경우 더 강력한 데미지를 준다.*/
void AM4Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	CheckNull(OtherActor);
	ABaseZombie* Zombie = Cast<ABaseZombie>(OtherActor);
	CheckNull(Zombie);
	FDamageEvent e;
	if(Hit.BoneName==FName("Head_M")||Hit.BoneName==FName("HeadEnd_M"))
	{
		CLog::Print("HeadShot");
		Zombie->TakeDamage(Damage*5.0f, e, UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	}
	else
	{
		Zombie->TakeDamage(Damage, e, UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
	}
	Destroy();
}

