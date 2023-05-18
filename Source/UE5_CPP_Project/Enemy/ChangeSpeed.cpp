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

/**BT에서 만약 플레이어를 발견했을경우 || 플레어가 쏜 총알소리가 들릴경우 이동속도를 변경*/
void UChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	auto controller = OwnerComp.GetAIOwner();
	ABaseZombie* zombie = Cast<ABaseZombie>(controller->GetPawn());
	zombie->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

/**서비스에 설명*/
FString UChangeSpeed::GetStaticServiceDescription()
{
	return FString("Change the Zombies Speed");
}
