/**MainPlayer AnimInstance ABP�� ���� Class*/
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerAnimInstance.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UMainPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Falling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Sprint;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Aim;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Fire;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Reload;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool Die;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Yaw;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class AMainPlayer* Player;
};
