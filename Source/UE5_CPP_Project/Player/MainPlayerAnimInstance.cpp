#include "Player/MainPlayerAnimInstance.h"
#include "Global.h"
#include "Components/StateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MainPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

void UMainPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

/**ABP 를 위한 이벤트 처리 각 메인 플레이어에 애님 State에 필요한 변수 값들을 갱신후 적용해준다.*/
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
	Aim = Player->GetAim();
	Fire = Player->GetState()->IsFireMode();
	Reload = Player->GetReload();
	FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(Player->GetControlRotation(), Player->GetActorRotation());
	FRotator Interp = FMath::RInterpTo(FRotator(Pitch, Yaw, 0.0f), Delta, GetDeltaSeconds(), 5.0f);
	
	float PitchAngle = Interp.Pitch;
	float YawAngle = Interp.Yaw;
	Pitch = FMath::ClampAngle(PitchAngle,-90.f,90.f);
	Yaw = FMath::ClampAngle(YawAngle,-90.f,90.f);
	Die = Player->DieAnimationing;
}
