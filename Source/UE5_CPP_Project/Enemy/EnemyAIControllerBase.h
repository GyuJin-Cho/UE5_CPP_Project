#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIControllerBase.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AEnemyAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	FORCEINLINE class UBlackboardComponent* GetBlackBoard() { return BBC; }

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BTC;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BBC;

};
