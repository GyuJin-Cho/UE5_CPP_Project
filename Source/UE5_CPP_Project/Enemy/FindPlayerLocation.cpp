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

/**플레이어를 발견했으면 Player Location을 갱신하여 쫒아갑니다.*/
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
			controller->GetBlackBoard()->SetValueAsVector(GetSelectedBlackboardKey(),navlocation.Location);
		}
	}
	else
	{
		controller->GetBlackBoard()->SetValueAsVector(GetSelectedBlackboardKey(), playerlocation);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
