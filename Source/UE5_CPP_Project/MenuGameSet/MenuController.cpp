#include "MenuGameSet/MenuController.h"
#include "Global.h"
#include "Widgets/MenuWidget.h"

/**ó�� ���۵� Menu�� CDO���� �����´�.*/
AMenuController::AMenuController()
{
	CHelpers::GetClass<UMenuWidget>(&MenuWidgetClass, "WidgetBlueprint'/Game/Menu/MenuWidget.MenuWidget_C'");
}

/**Menu�� ViewPort�� ����� Visibility�� ���� Menu�� �����ش�.*/
/**Controller�� ���� ������ SetMouseCursor�Լ��� ����ϱ� ����*/
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
