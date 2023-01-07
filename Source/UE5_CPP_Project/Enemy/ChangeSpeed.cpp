#include "Enemy/ChangeSpeed.h"
#include "BaseZombie.h"
#include "Global.h"
#include "EnemyAIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UChangeSpeed::UChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	auto controller = OwnerComp.GetAIOwner();
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());
	zombie->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

FString UChangeSpeed::GetStaticServiceDescription()
{
	return FString("Change the Zombies Speed");
}
