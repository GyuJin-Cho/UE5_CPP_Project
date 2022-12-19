#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArmoComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_CPP_PROJECT_API UArmoComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	int Armo;
	int MaxArmo = 30;

public:	
	UArmoComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE int GetArmo() { return Armo; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE int GetMaxArmo() { return MaxArmo; }
	void SetArmo(int Arm);
};
