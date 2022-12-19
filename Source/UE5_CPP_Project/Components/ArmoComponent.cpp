#include "Components/ArmoComponent.h"

UArmoComponent::UArmoComponent()
{
	MaxArmo = 30;
}


void UArmoComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UArmoComponent::SetArmo(int Arm)
{
	Armo = Arm;
	
}

