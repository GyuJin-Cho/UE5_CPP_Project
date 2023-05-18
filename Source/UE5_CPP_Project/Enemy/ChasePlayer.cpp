#include "Enemy/ChasePlayer.h"
#include "Global.h"
#include "EnemyAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackBoard_Keys.h"
UChasePlayer::UChasePlayer(const FObjectInitializer& FObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

/**플레이어를 따라다니는 Task BT 에 데코레이션에 조건이 맞을경우*/
EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	FVector PlayerLocation = controller->GetBlackBoard()->GetValueAsVector(GetSelectedBlackboardKey());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, PlayerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
