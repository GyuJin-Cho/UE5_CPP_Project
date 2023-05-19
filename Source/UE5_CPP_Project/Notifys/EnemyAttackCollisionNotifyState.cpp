#include "Notifys/EnemyAttackCollisionNotifyState.h"
#include "Global.h"
#include "Enemy/BaseZombie.h"
FString UEnemyAttackCollisionNotifyState::GetNotifyName_Implementation() const
{
	return "EnemyAttackCollision";
}

/**Notify ������ Zombie �� ����(���� �ִϸ��̼� Ȱ��)�� Collision On*/
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

/**Notify ���� Zombie �� ������ ����(���� �ִϸ��̼� ����)�� Collision Off*/
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
