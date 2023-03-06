#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	AMenuController();

	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UMenuWidget> MenuWidgetClass;

	class UMenuWidget* MenuWidget;
};
