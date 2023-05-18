#include "Enemy/WomanZombie.h"
#include "Global.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SphereComponent.h"

/**여성형 좀비는 mesh가 다르고 애니메이션도 다르기때문에 CDO 즉 생성자를 통해 다시 정의*/
AWomanZombie::AWomanZombie()
{
	CHelpers::GetAsset<USkeletalMesh>(&Mesh, "SkeletalMesh'/Game/EnemyZombie/WomanZombie/Mesh/ZombieD_V1.ZombieD_V1'");
	GetMesh()->SetSkeletalMesh(Mesh);
	CHelpers::GetClass<UAnimInstance>(&AnimInstance, "AnimBlueprint'/Game/EnemyZombie/WomanZombie/ABP/ABP_WomanZombie.ABP_WomanZombie_C'");
	GetMesh()->SetAnimInstanceClass(AnimInstance);
	SphereComponentHand->SetSphereRadius(30.0f);
	CHelpers::GetAsset<UAnimMontage>(&Montages, "AnimMontage'/Game/EnemyZombie/WomanZombie/Montage/Anim_Monster_Attack_1_Montage.Anim_Monster_Attack_1_Montage'");
}

void AWomanZombie::BeginPlay()
{
	Super::BeginPlay();
}

void AWomanZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWomanZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
