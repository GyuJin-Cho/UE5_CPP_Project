#include "Notifys/EnemyAttackCollisionNotifyState.h"
#include "Global.h"
#include "Enemy/BaseZombie.h"
FString UEnemyAttackCollisionNotifyState::GetNotifyName_Implementation() const
{
	return "EnemyAttackCollision";
}

/**Notify 시작점 Zombie 의 공격(공격 애니메이션 활성)시 Collision On*/
void UEnemyAttackCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AActor* actor = MeshComp->GetOwner();
	ABaseZombie* zombie = nullptr;

	if (actor)
		zombie = Cast<ABaseZombie>(actor);

	if (zombie)
		zombie->CollisionOn();
}

/**Notify 끝점 Zombie 의 공격이 끝날(공격 애니메이션 종료)시 Collision Off*/
void UEnemyAttackCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AActor* actor = MeshComp->GetOwner();
	ABaseZombie* zombie = nullptr;

	if (actor)
		zombie = Cast<ABaseZombie>(actor);

	if (zombie)
		zombie->CollisionOff();
}
