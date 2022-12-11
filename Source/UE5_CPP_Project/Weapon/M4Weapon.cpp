#include "Weapon/M4Weapon.h"
#include "Global.h"
#include "Player/MainPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
AM4Weapon::AM4Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Mesh, "M4", GetRootComponent());

}

void AM4Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AM4Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AM4Weapon::Equip(AMainPlayer* Player)
//{
//	
//}