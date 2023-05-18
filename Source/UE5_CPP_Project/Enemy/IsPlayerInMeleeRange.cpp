#include "Enemy/IsPlayerInMeleeRange.h"
#include "Global.h"
#include "EnemyAIControllerBase.h"
#include "BaseZombie.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoard_Keys.h"

UIsPlayerInMeleeRange::UIsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("IsPlayerInMeleeRange");
}

/**Player와 가까이 붙으면 실행되는 함수 Player와 좀비의 거리가 설정한 값보다 가까워지면 그 즉시 좀비의 조건을 변경한다.*/
void UIsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AEnemyAIControllerBase* const cont = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	ABaseZombie* const zombie = Cast<ABaseZombie>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	float const distance = zombie->GetDistanceTo(player);

	//CLog::Print(distance);

	cont->GetBlackBoard()->SetValueAsBool(GetSelectedBlackboardKey(), distance <= MeleeRange);
}