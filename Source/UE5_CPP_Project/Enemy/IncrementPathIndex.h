/**PatrolIndex를 얻기위한 Task*/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "IncrementPathIndex.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UIncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UIncrementPathIndex(const FObjectInitializer& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	enum class EDirectionType
	{
		Forward, Revers
	};

	EDirectionType Direction = EDirectionType::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		bool bIDirectional = true;
};
