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

/**Set Move �̵��� true�� ��ȯ*/
void UStatusComponent::SetMove()
{
	bCanMove = true;
}

/**Set Move ������ true�� ��ȯ*/
void UStatusComponent::SetStop()
{
	bCanMove = false;
}

/**�ӵ� enum�� ���� �ӵ� ��ȭ*/
void UStatusComponent::SetSpeed(ECharacterSpeed InSpeed)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());

	movement->MaxWalkSpeed = Speed[(int32)InSpeed];
}

/**ü�� ȸ�� �Լ�*/
void UStatusComponent::AddHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

/**������ ���ҽ� ü�� ����*/
void UStatusComponent::SubHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}