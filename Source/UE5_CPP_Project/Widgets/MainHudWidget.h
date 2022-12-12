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
};
