/**RecoilNotify*/
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RecoilNotify.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API URecoilNotify : public UAnimNotify
{
	GENERATED_BODY()

	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
