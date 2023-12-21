#include "Spawner/ZombieSpawnTriger.h"
#include "Global.h"
#include "ZombieSpawner.h"
#include "Components/BoxComponent.h"
#include "Enemy/BaseZombie.h"
#include "Enemy/ManZombie.h"
#include "Player/MainPlayer.h"
#include "Enemy/WomanZombie.h"
#include "Widgets/MainHudWidget.h"

/**ZombieSpawnTriger ������ CDO�� ���� Component ���� �� ������� BP���� �����´�.*/
AZombieSpawnTriger::AZombieSpawnTriger()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Box, "BoxCollision");
	CHelpers::GetClass<ABaseZombie>(&BaseZombie, "Blueprint'/Game/EnemyZombie/ZombieBase/BaseZombie_BP.BaseZombie_BP_C'");
	CHelpers::GetClass<AManZombie>(&ManZombie, "Blueprint'/Game/EnemyZombie/ManZombie/ManZombie.ManZombie_C'");
	CHelpers::GetClass<AWomanZombie>(&WomanZombie, "Blueprint'/Game/EnemyZombie/WomanZombie/WomanZombie_BP.WomanZombie_BP_C'");
}

/**���� ������ Box Collision�� �̺�Ʈ ���ε�*/
void AZombieSpawnTriger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AZombieSpawnTriger::OnBeginOverlap);
	
}

void AZombieSpawnTriger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**Player�� Overlap�� ������� ��ϵ� ZombieSpawners���� Spawn�Ѵ� Type�� FMath�� ����Ͽ� �����ϰ� Spawn�Ѵ�.*/
/**������ SpawnTriger�� �����Ѵ�.*/
void AZombieSpawnTriger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* player = Cast<AMainPlayer>(OtherActor);
	if(player)
	{
		for (int i = 0; i < ZombieSpawners.Num(); i++)
		{
			int32 ZombieTypeNum = FMath::RandRange(MinRange, MaxRange);
			switch (ZombieTypeNum)
			{
			case 0:
			{
				GetWorld()->SpawnActor<ABaseZombie>(BaseZombie, ZombieSpawners[i]->GetTransform());
				break;
			}
			case 1:
			{
				GetWorld()->SpawnActor<ABaseZombie>(ManZombie, ZombieSpawners[i]->GetTransform());
				break;
			}
			case 2:
			{
				GetWorld()->SpawnActor<ABaseZombie>(WomanZombie, ZombieSpawners[i]->GetTransform());
				break;
			}
			}
		}
		UMainHudWidget* Hud = player->GetMainHudWidget();
		if (Hud)
		{
			Hud->SetEnemyCount(ZombieSpawners.Num(), false);
		}
		Destroy();
	}
}

