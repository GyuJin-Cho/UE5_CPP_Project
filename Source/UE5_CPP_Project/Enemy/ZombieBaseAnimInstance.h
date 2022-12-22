#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieBaseAnimInstance.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UZombieBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Die;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ABaseZombie* Player;
};
