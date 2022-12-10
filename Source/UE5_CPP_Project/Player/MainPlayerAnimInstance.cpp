#include "Player/MainPlayerAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MainPlayer.h"


void UMainPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	
}

void UMainPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();

	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());

	Player = Cast<AMainPlayer>(character);
	Falling = Player->GetCharacterMovement()->IsFalling();
	Sprint = Player->GetSprint();
}
