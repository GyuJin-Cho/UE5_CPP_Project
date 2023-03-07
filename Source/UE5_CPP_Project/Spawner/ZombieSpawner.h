#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawner.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AZombieSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AZombieSpawner();

protected:
	virtual void BeginPlay() override;


};
