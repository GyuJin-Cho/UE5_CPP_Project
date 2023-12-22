/**MainHudWidget Class BP를 활용하기 위해 전 함수 BlueprintImplementableEvent를 설정해주고 BP에서 정의해준다.*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHudWidget.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API UMainHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void HealthUpdate(float InHealth, float InMaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
		void StaminaUpdate(float InStamina, float InMaxStamina);

	UFUNCTION(BlueprintImplementableEvent)
		void DecreaseArmo(int Armo);

	UFUNCTION(BlueprintImplementableEvent)
		void Reload(int MaxArmo);

	UFUNCTION(BlueprintImplementableEvent)
		void IsAuto(bool IsAuto);

	UFUNCTION(BlueprintImplementableEvent)
		void SetMaxArmo(int MaxArmo);

	UFUNCTION(BlueprintImplementableEvent)
		void SetEnemyCount(int EnemyCount, bool IsDeath);

	UFUNCTION(BlueprintImplementableEvent)
		void SetTargetText(const FString& Text);
};
