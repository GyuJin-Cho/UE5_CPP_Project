#include "Enemy/FindRandomLocation.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyAIControllerBase.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoard_Keys.h"
#include "BaseZombie.h"

UFindRandomLocation::UFindRandomLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Find Target Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemyAIControllerBase* Controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());

	APawn* pawn = Controller->GetPawn();

	ABaseZombie* Zombie = Cast<ABaseZombie>(pawn);

	if (Zombie->GetDie())
		return EBTNodeResult::Failed;

	if(!pawn)
	{
		CLog::Print("Pawn Error");
		return EBTNodeResult::Failed;
	}
	FVector origin = pawn->GetActorLocation();
	FNavLocation Location;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(NavSystem->GetRandomPointInNavigableRadius(origin,SearchRadius,Location,nullptr))
	{
		Controller->GetBlackBoard()->SetValueAsVector(bb_Keys::TargetLocation, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
