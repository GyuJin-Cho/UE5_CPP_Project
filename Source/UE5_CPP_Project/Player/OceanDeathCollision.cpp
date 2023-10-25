#include "Player/OceanDeathCollision.h"
#include "Player/MainPlayer.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AOceanDeathCollision::AOceanDeathCollision()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent(this, &BoxComponent, "BoxComponent");
}

void AOceanDeathCollision::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOceanDeathCollision::OnBeginOverlapDie);
}

/**player¶û Á¢ÃË½Ã ±× Áï½Ã Áï»ç*/
void AOceanDeathCollision::OnBeginOverlapDie(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);
	AMainPlayer * player = Cast<AMainPlayer>(OtherActor);
	if(IsValid(player))
	{
		player->Die();
	}
}

void AOceanDeathCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

