#include "Enemy/MeleeAttack.h"
#include "Global.h"
#include "EnemyAIControllerBase.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "BaseZombie.h"

UMeleeAttack::UMeleeAttack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("MeleeAttack");
}

/**조건에 부합하면 실행되는 함수로 Zombie에 MeleeAttack함수를 실행한다.*/
/**만약 Montage가 실행중이면 if문에서 false처리가 되어 MeleeAttack함수를 실행을 안한다.*/
EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	

	if(ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn()))
	{
		if(MontageHasFinished(zombie))
		{
			zombie->MeleeAttack();
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

/**만약 Montage가 실행중이면 false를 리턴.*/
bool UMeleeAttack::MontageHasFinished(ABaseZombie* Zombie)
{
	return Zombie->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Zombie->GetMontage());
}
