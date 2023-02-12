#include "Enemy/StopInvestingating.h"
#include "EnemyAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoard_Keys.h"


UStopInvestingating::UStopInvestingating(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Stop Investigating");
}

EBTNodeResult::Type UStopInvestingating::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemyAIControllerBase* Controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	Controller->GetBlackBoard()->SetValueAsBool(GetSelectedBlackboardKey(), false);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
