#include "Enemy/EnemyAIControllerBase.h"
#include "Global.h"
#include "BaseZombie.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BlackBoard_Keys.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/Engine.h"
#include "Player/MainPlayer.h"
#include "AI_Tags.h"
#include "GameFramework/Character.h"

/**CDO을 통해 BT, BTComponent, BBComponent를 생성 및 총소리 및 플레이어의 탐지 거리여부를 조정하는 생성자.*/
AEnemyAIControllerBase::AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/EnemyZombie/ZombieBase/AI/Behavior/BT.BT'");

	CHelpers::CreateActorComponent<UBehaviorTreeComponent>(this,&BTC, "BehaviorTreeComponent");
	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &BBC, "BlackBoardComponent");

	/*SetupPerceptionSystem();*/

	CHelpers::CreateActorComponent<UAISenseConfig_Sight>(this, &Sight, "Sight Config");
	if (Sight)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		Sight->SightRadius = 500.0f;
		Sight->LoseSightRadius = Sight->SightRadius + 25.0f;
		Sight->PeripheralVisionAngleDegrees = 90.0f;
		Sight->SetMaxAge(5.0f);
		Sight->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		Sight->DetectionByAffiliation.bDetectEnemies = true;
		Sight->DetectionByAffiliation.bDetectFriendlies = true;
		Sight->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*Sight->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIControllerBase::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*Sight);
	}

	CHelpers::CreateActorComponent<UAISenseConfig_Hearing>(this, &HearingConfig, "Hearing Config");
	if (HearingConfig)
	{
		HearingConfig->HearingRange = 3000.0f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies =
			HearingConfig->DetectionByAffiliation.bDetectFriendlies =
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIControllerBase::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*HearingConfig);
	}

}

/**게임이 시작과 동시에 BT를 실행한다.*/
void AEnemyAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BTC->StartTree(*BehaviorTree);
}

/**브랙보드를 초기화하는 함수 OnPossess는 현재 가지고있는 폰을 빙의한다.*/
void AEnemyAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}

}

/**플레이어를 찾는함수*/
void AEnemyAIControllerBase::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	
	if(AMainPlayer* ch = Cast<AMainPlayer>(Actor))
	{
		GetBlackBoard()->SetValueAsBool(bb_Keys::CanSeePlayer, Stimulus.WasSuccessfullySensed());
	}
}

/**좀비 자신이 총소리가 들리는지 플레이어가 감지되는지 계속 업데이트를 통해 찾는다.*/
void AEnemyAIControllerBase::OnUpdated(TArray<AActor*> const& UpdatedActors)
{
	for(int x = 0; x<UpdatedActors.Num();x++)
	{
		FActorPerceptionBlueprintInfo info;
		GetPerceptionComponent()->GetActorsPerception(UpdatedActors[x], info);
		for(int k = 0; k < info.LastSensedStimuli.Num(); k++)
		{
			FAIStimulus const stimulus = info.LastSensedStimuli[k];
			if(stimulus.Tag == tags::noise_tag)
			{
				GetBlackBoard()->SetValueAsBool(bb_Keys::ISInvestigating, stimulus.WasSuccessfullySensed());
				GetBlackBoard()->SetValueAsVector(bb_Keys::TargetLocation, stimulus.StimulusLocation);

			}
			else
			{
				GetBlackBoard()->SetValueAsBool(bb_Keys::CanSeePlayer, stimulus.WasSuccessfullySensed());
			}

		}
	}
}

//void AEnemyAIControllerBase::SetupPerceptionSystem()
//{
//}

