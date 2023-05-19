#include "ClearActor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayer.h"
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

/**목적지까지 가면 이 BoxCollision에 밟혀 게임을 정상적으로 완수할수 있다.*/
void AClearActor::OnBeginOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* player = Cast<AMainPlayer>(OtherActor);
	if(player == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		player->Clear();
	}
}

