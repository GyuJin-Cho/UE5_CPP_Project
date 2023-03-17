#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverClearWidget.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UGameOverClearWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Clear();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();
};
