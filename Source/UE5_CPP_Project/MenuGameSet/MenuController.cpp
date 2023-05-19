#include "MenuGameSet/MenuController.h"
#include "Global.h"
#include "Widgets/MenuWidget.h"

/**처음 시작된 Menu를 CDO에서 가져온다.*/
AMenuController::AMenuController()
{
	CHelpers::GetClass<UMenuWidget>(&MenuWidgetClass, "WidgetBlueprint'/Game/Menu/MenuWidget.MenuWidget_C'");
}

/**Menu를 ViewPort에 등록후 Visibility를 통해 Menu를 보여준다.*/
/**Controller에 놓은 이유는 SetMouseCursor함수를 사용하기 위함*/
void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
		MenuWidget->AddToViewport();
		MenuWidget->SetVisibility(ESlateVisibility::Visible);
	}

	SetShowMouseCursor(true);
}
