#include "Enemy/EnemyAIControllerBase.h"
#include "Global.h"
#include "BaseZombie.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AEnemyAIControllerBase::AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/EnemyZombie/ZombieBase/AI/Behavior/BT.BT'");

	CHelpers::CreateActorComponent<UBehaviorTreeComponent>(this,&BTC, "BehaviorTreeComponent");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &BBC, "BlackBoardComponent");
}

void AEnemyAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BTC->StartTree(*BehaviorTree);
}

void AEnemyAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}

}
