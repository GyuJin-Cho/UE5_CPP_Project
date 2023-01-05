#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindPatrolPathPoint.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UFindPatrolPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindPatrolPathPoint(const FObjectInitializer& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
