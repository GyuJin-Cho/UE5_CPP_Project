#include "Enemy/FindPatrolPathPoint.h"
#include "Global.h"
#include "Enemy/BaseZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyAIControllerBase.h"
#include "BlackBoard_Keys.h"
UFindPatrolPathPoint::UFindPatrolPathPoint(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("FindPatrolPathPoint");
}

/**좀비 에게서 등록된 APatrolPath가 있으면 그 위치를 가져온다.*/
EBTNodeResult::Type UFindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());

	int index = controller->GetBlackBoard()->GetValueAsInt(bb_Keys::PatrolPathIndex);

	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());
	FVector point = zombie->GetPatrolPath()->GetPatrolPoint(index);

	FVector GlobalPoint = zombie->GetPatrolPath()->GetActorTransform().TransformPosition(point);

	controller->GetBlackBoard()->SetValueAsVector(PatrolPathvectorKey.SelectedKeyName, GlobalPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
