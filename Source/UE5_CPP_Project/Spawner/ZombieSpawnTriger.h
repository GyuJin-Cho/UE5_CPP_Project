#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawnTriger.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AZombieSpawnTriger : public AActor
{
	GENERATED_BODY()
	
public:	
	AZombieSpawnTriger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZombieSpaners", meta = (AllowPrivateAccess = "true"))
		TArray<class AZombieSpawner*> ZombieSpawners;

	class UBoxComponent* Box;
	UPROPERTY(EditDefaultsOnly, Category = "BaseZombie",meta=(AllowPrivateAccess = "true"))
		TSubclassOf<class ABaseZombie> BaseZombie;

	UPROPERTY(EditDefaultsOnly, Category = "BaseZombie", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AManZombie> ManZombie;

	UPROPERTY(EditDefaultsOnly, Category = "BaseZombie", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AWomanZombie> WomanZombie;

	const int MinRange = 0;
	const int MaxRange = 2;

};
