/**GameOverClearWidget Class Clear GameOver 함수들을 BP에서 사용하기 위해 BlueprintImplementableEvent로 설정해준다.*/
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
