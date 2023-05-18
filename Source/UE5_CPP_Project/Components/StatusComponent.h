/**Status Component 체력과 현재 걷는지 뛰는지의 상태를 얻는 Component*/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

enum class ECharacterSpeed : uint8
{
	Walk, Run, Sprint, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_CPP_PROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

	void SetMove();
	void SetStop();

	void SetSpeed(ECharacterSpeed InSpeed);

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ECharacterSpeed::Max] = { 200, 400, 600 };

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ECharacterSpeed::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ECharacterSpeed::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ECharacterSpeed::Sprint]; }

	FORCEINLINE bool CanMove() { return  bCanMove; }
private:
	float Health = 100.0f;

	bool bCanMove = true;
};
