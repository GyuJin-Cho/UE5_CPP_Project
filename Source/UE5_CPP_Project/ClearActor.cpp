#include "ClearActor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayer.h"
#include "Weapon/M4Weapon.h"
#include "Widgets/GameOverClearWidget.h"

AClearActor::AClearActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Box, "BoxCollision", GetRootComponent());
	
}

void AClearActor::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AClearActor::OnBeginOverlapEnd);
}

void AClearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClearActor::OnBeginOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* player = Cast<AMainPlayer>(OtherActor);
	if(player == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		player->Clear();
	}
}

