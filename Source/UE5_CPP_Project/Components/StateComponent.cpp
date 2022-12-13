#include "Components/StateComponent.h"
#include "Global.h"

UStateComponent::UStateComponent()
{

}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetFireMode()
{
	ChangeType(EStateType::Fire);
}

void UStateComponent::SetAimMode()
{
	ChangeType(EStateType::Aim);
}

void UStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prev, InNewType);
}
