#include "Enemy/ZombieBaseAnimInstance.h"
#include "Global.h"
#include "BaseZombie.h"
void UZombieBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

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
