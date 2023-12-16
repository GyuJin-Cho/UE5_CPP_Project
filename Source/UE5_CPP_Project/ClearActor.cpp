#include "ClearActor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayer.h"
#include "Enemy/BaseZombie.h"
#include "Weapon/M4Weapon.h"
#include "Widgets/GameOverClearWidget.h"

/**생성자 BoxCollision Component를 CDO중에 부착한다.*/
AClearActor::AClearActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Box, "BoxCollision", GetRootComponent());
	
}

/**게임 시작중에 Box를 이벤트 바인딩 한다.*/
void AClearActor::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AClearActor::OnBeginOverlapEnd);
}

void AClearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**목적지까지 가면 이 BoxCollision에 밟혀 게임이 만약 마지막 스테이지면 클리어 아니면 다음 레벨*/
/**좀비들을 다 죽여야 한다.*/
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

