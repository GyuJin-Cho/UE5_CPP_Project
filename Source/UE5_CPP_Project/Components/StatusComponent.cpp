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

/**Set Move 이동시 true로 변환*/
void UStatusComponent::SetMove()
{
	bCanMove = true;
}

/**Set Move 정지시 true로 변환*/
void UStatusComponent::SetStop()
{
	bCanMove = false;
}

/**속도 enum에 따라 속도 변화*/
void UStatusComponent::SetSpeed(ECharacterSpeed InSpeed)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());

	movement->MaxWalkSpeed = Speed[(int32)InSpeed];
}

/**체력 회복 함수*/
void UStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

/**공격을 당할시 체력 제거*/
void UStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}