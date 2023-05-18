#include "Enemy/ZombieBaseAnimInstance.h"
#include "Global.h"
#include "BaseZombie.h"
void UZombieBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

/**애니메이션 BP에 이벤트 처리를 위한 함수 실시간으로 좀비의 상태를 받아 알맞는 애니메이션을 실행시켜준다.*/
void UZombieBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();

	ABaseZombie* Zombie = Cast<ABaseZombie>(character);
	CheckNull(Zombie);

	Die = Zombie->GetDie();
}
