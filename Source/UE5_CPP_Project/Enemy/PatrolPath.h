#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolPath();

	FORCEINLINE FVector GetPatrolPoint(const int index)const {return PatrolPoint[index]; }
	FORCEINLINE int num()const { return PatrolPoint.Num(); }
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
		TArray<FVector> PatrolPoint;

};
