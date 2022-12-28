#include "Enemy/FindPlayerLocation.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Enemy/EnemyAIControllerBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "GameFramework/Character.h"
#include "BlackBoard_Keys.h"
UFindPlayerLocation::UFindPlayerLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());

	FVector playerlocation = player->GetActorLocation();
	if (SearchRandom)
	{
		FNavLocation navlocation;

		UNavigationSystemV1* navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if(navsystem->GetRandomPointInNavigableRadius(playerlocation,SearchRadius,navlocation,nullptr))
		{
			controller->GetBlackBoard()->SetValueAsVector(bb_Keys::TargetLocation,navlocation.Location);
		}
	}
	else
	{
		controller->GetBlackBoard()->SetValueAsVector(bb_Keys::TargetLocation, playerlocation);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
