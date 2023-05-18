#include "Components/StateComponent.h"
#include "Global.h"

UStateComponent::UStateComponent()
{

}

void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

/**Idle Mode Set*/
void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

/**Fire Mode Set*/
void UStateComponent::SetFireMode()
{
	ChangeType(EStateType::Fire);
}

/**Aim Mode Set*/
void UStateComponent::SetAimMode()
{
	ChangeType(EStateType::Aim);
}

/**Hit Mode Set*/
void UStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

/**Dead Mode Set*/
void UStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

/**실질적으로 Type을 변경하는 구간*/
void UStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	//if (OnStateTypeChanged.IsBound())
	//	OnStateTypeChanged.Broadcast(prev, InNewType);
}
