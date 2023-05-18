/**좀비와 플레이어와에 거리가 가까워지면 Service를 통해 조건을 변경하여 공격을 할수있게 만드는 Service*/
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInMeleeRange.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UIsPlayerInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UIsPlayerInMeleeRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float MeleeRange = 25.0f;
};
