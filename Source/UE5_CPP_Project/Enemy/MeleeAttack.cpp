#include "Enemy/MeleeAttack.h"
#include "Global.h"
#include "CombatInterface.h"
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

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());

	if(ICombatInterface* Icombat = Cast<ICombatInterface>(zombie))
	{
		if(MontageHasFinished(zombie))
		{
			Icombat->Execute_melee_attack(zombie);
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMeleeAttack::MontageHasFinished(ABaseZombie* Zombie)
{
	return Zombie->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(Zombie->GetMontage());
}
