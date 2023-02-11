#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "StopInvestingating.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UStopInvestingating : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UStopInvestingating(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
