#include "Components/ArmoComponent.h"

/**생성자 */
UArmoComponent::UArmoComponent()
{
	MaxArmo = 30;
}


void UArmoComponent::BeginPlay()
{
	Super::BeginPlay();

}

/**Set Armo 재정전 될때 여길 통해 현재 Armo에 상태를 변경해준다.*/
void UArmoComponent::SetArmo(int Arm)
{
	Armo = Arm;
	
}

