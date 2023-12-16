#include "ClearActor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayer.h"
#include "Enemy/BaseZombie.h"
#include "Weapon/M4Weapon.h"
#include "Widgets/GameOverClearWidget.h"

/**������ BoxCollision Component�� CDO�߿� �����Ѵ�.*/
AClearActor::AClearActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Box, "BoxCollision", GetRootComponent());
	
}

/**���� �����߿� Box�� �̺�Ʈ ���ε� �Ѵ�.*/
void AClearActor::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AClearActor::OnBeginOverlapEnd);
}

void AClearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**���������� ���� �� BoxCollision�� ���� ������ ���� ������ ���������� Ŭ���� �ƴϸ� ���� ����*/
/**������� �� �׿��� �Ѵ�.*/
void AClearActor::OnBeginOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* player = Cast<AMainPlayer>(OtherActor);
	TArray<AActor*> Zombies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseZombie::StaticClass(), Zombies);
	if(player == UGameplayStatics::GetPlayerCharacter(GetWorld(),0)&&Zombies.IsEmpty())
	{
		player->Clear();
	}
}

