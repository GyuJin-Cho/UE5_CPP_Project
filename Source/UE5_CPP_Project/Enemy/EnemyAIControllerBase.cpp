#include "Enemy/EnemyAIControllerBase.h"
#include "Global.h"
#include "BaseZombie.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BlackBoard_Keys.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Player/MainPlayer.h"

AEnemyAIControllerBase::AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/EnemyZombie/ZombieBase/AI/Behavior/BT.BT'");

	CHelpers::CreateActorComponent<UBehaviorTreeComponent>(this,&BTC, "BehaviorTreeComponent");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &BBC, "BlackBoardComponent");

	SetupPerceptionSystem();
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

void AEnemyAIControllerBase::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	
	if(AMainPlayer* ch = Cast<AMainPlayer>(Actor))
	{
		GetBlackBoard()->SetValueAsBool(bb_Keys::CanSeePlayer, Stimulus.WasSuccessfullySensed());
	}
}

void AEnemyAIControllerBase::SetupPerceptionSystem()
{
	CHelpers::CreateActorComponent<UAISenseConfig_Sight>(this, &Sight, "Sight Config");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	Sight->SightRadius = 500.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 50.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f;
	Sight->SetMaxAge(5.0f);
	Sight->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*Sight->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIControllerBase::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*Sight);
}
