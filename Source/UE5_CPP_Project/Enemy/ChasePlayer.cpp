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

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	FVector PlayerLocation = controller->GetBlackBoard()->GetValueAsVector(GetSelectedBlackboardKey());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, PlayerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
