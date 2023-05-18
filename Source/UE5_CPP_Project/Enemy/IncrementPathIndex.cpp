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

/**실직적인 Patrol 함수 patrol을 놓은 레벨에서 한 곳에 도착하면 다른 한곳에 인덱스를 받아 그곳으로 움직이게 한다.*/
EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());
	int NoOfPoint = zombie->GetPatrolPath()->num();
	int MinIndex = 0;
	int MaxIndex = NoOfPoint - 1;

	int index = controller->GetBlackBoard()->GetValueAsInt(GetSelectedBlackboardKey());

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

	controller->GetBlackBoard()->SetValueAsInt(GetSelectedBlackboardKey(),
		(Direction == EDirectionType::Forward ? abs(++index) : abs(--index))%NoOfPoint);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
