#include "Enemy/IncrementPathIndex.h"
#include "Global.h"
#include "Enemy/BlackBoard_Keys.h"
#include "EnemyAIControllerBase.h"
#include "BaseZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <cmath>

UIncrementPathIndex::UIncrementPathIndex(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("IncrementPathIndex");
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());
	int NoOfPoint = zombie->GetPatrolPath()->num();
	int MinIndex = 0;
	int MaxIndex = NoOfPoint - 1;

	int index = controller->GetBlackBoard()->GetValueAsInt(bb_Keys::PatrolPathIndex);

	if(bIDirectional)
	{
		if (index >= MaxIndex && Direction == EDirectionType::Forward)
		{
			Direction = EDirectionType::Revers;
		}
		else if (index == MinIndex && Direction == EDirectionType::Revers)
		{
			Direction = EDirectionType::Forward;
		}
	}

	controller->GetBlackBoard()->SetValueAsInt(bb_Keys::PatrolPathIndex, 
		(Direction == EDirectionType::Forward ? abs(++index) : abs(--index))%NoOfPoint);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
