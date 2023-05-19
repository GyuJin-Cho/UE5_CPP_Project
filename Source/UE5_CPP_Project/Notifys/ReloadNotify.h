/**ReloadNotify*/
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ReloadNotify.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UReloadNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
