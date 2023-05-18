/**MeleeAttack Task 조건이 부합하면 BT를 통해 실행*/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BaseZombie.h"
#include "MeleeAttack.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UMeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMeleeAttack(const FObjectInitializer& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool MontageHasFinished(ABaseZombie* Zombie);
};
