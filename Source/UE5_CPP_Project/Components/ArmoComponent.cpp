#include "Components/ArmoComponent.h"

/**������ */
UArmoComponent::UArmoComponent()
{
	MaxArmo = 30;
}


void UArmoComponent::BeginPlay()
{
	Super::BeginPlay();

}

/**Set Armo ������ �ɶ� ���� ���� ���� Armo�� ���¸� �������ش�.*/
void UArmoComponent::SetArmo(int Arm)
{
	Armo = Arm;
	
}

