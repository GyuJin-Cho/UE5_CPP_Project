#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Player/MainPlayer.h"
#include "UE5_CPP_ProjectGameInstance.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UUE5_CPP_ProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	EStateTLevel Type;
	FORCEINLINE EStateTLevel GetLevel() { return Type; }
	void SetLevel(const EStateTLevel& type);
};
