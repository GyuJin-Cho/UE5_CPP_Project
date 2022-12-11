#include "Components/StatusComponent.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UStatusComponent::SetMove()
{
	bCanMove = true;
}

void UStatusComponent::SetStop()
{
	bCanMove = false;
}

void UStatusComponent::SetSpeed(ECharacterSpeed InSpeed)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());

	movement->MaxWalkSpeed = Speed[(int32)InSpeed];
}

void UStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UStatusComponent::AddStamina(float InAmount)
{
	Stamina += InAmount;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

void UStatusComponent::SubStamina(float InAmount)
{
	Stamina -= InAmount;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}