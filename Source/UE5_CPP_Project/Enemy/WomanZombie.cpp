#include "Enemy/WomanZombie.h"
#include "Global.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SphereComponent.h"
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
