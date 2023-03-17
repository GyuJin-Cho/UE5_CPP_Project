#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClearActor.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AClearActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AClearActor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* Box;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
