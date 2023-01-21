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
	NodeName = TEXT("IsPlayerInMeleeRange");
}

void UIsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AEnemyAIControllerBase* controller = Cast<AEnemyAIControllerBase>(OwnerComp.GetAIOwner());
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	controller->GetBlackBoard()->SetValueAsBool(bb_Keys::PlayerIsInMeleeRange, zombie->GetDistanceTo(player) <= MeleeRange);

}
