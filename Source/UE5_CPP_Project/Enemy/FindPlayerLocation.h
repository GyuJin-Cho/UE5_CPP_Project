/*플레이어를 찾았으면 쫒아가는 클래스*/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindPlayerLocation.generated.h"

UCLASS(Blueprintable)
class UE5_CPP_PROJECT_API UFindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindPlayerLocation(const FObjectInitializer& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		bool SearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float SearchRadius = 150.0f;
};
