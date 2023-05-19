/**Zombie Spawner Class 좀비를 이 액터에 위치에 스폰한다.*/
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
