#pragma once
/**�������� ���� �ڵ� ��� �ݸ��� ����*/
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OceanDeathCollision.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AOceanDeathCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	AOceanDeathCollision();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		class UBoxComponent* BoxComponent;

	UFUNCTION()
		void OnBeginOverlapDie(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
public:	
	virtual void Tick(float DeltaTime) override;

};
