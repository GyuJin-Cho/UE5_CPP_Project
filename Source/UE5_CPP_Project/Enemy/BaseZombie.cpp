#include "Enemy/BaseZombie.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "Player/MainPlayer.h"
#include "Animation/AnimMontage.h"
#include "Engine/CollisionProfile.h"
#include "Widgets/MainHudWidget.h"
#include "EnemyAIControllerBase.h"

/**생성자 CDO를 통해 에셋 및 Component를 부착한다.*/
ABaseZombie::ABaseZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	CHelpers::GetAsset<USkeletalMesh>(&Mesh, "SkeletalMesh'/Game/EnemyZombie/ZombieBase/Mesh/BaseZombieA01.BaseZombieA01'");
	GetMesh()->SetSkeletalMesh(Mesh);
	CHelpers::CreateComponentSocket(this, &SphereComponentHand, "SphereComponentHand","AttackRightSocket", GetMesh());
	SphereComponentHand->SetSphereRadius(20.0f);
	CHelpers::GetClass<UAnimInstance>(&AnimInstance, "AnimBlueprint'/Game/EnemyZombie/ZombieBase/ABP/ABP_ZombieBase.ABP_ZombieBase_C'");
	GetMesh()->SetAnimInstanceClass(AnimInstance);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CHelpers::GetAsset<UAnimMontage>(&Montages, "AnimMontage'/Game/EnemyZombie/ZombieBase/Animation/Attack/Anim_Monster_Attack_1_Montage.Anim_Monster_Attack_1_Montage'");
	
}

/**beginplay 게임을 시작할때 실행되는 함수 Collision들을 AddDynamic을 통해 이벤트를 바인딩한다.*/
void ABaseZombie::BeginPlay()
{
	Super::BeginPlay();

	SphereComponentHand->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//SphereComponentHand->OnComponentHit.AddDynamic(this, &ABaseZombie::OnHit);
	SphereComponentHand->OnComponentBeginOverlap.AddDynamic(this, &ABaseZombie::OnBeginOverlapAttack);
	SphereComponentHand->OnComponentEndOverlap.AddDynamic(this, &ABaseZombie::OnEndOverlapAttack);
}

void ABaseZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CLog::Print(GetActorLocation());
}

void ABaseZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**TakeDamage 좀비가 총알에 맞으면 TakeDamage 함수가 실행된다.*/
/**데미지를 받는 곳에 파티클을 Spawn한다 (Blood Particle)*/
float ABaseZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (DieAnimationing)
		return 0.f;
	Health -= DamageAmount;
	if(HitParticle)
	{
		FVector Location = DamageCauser->GetActorLocation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Location, FRotator(0.0f), FVector(2.0f, 2.0f, 2.0f), false);
	}

	if(Health<=0)
	{
		Die();
	}
	

	return DamageAmount;
}

/**Health 가 0이되는 순간 Die 함수를 콜한다. 죽는 소리는 SoundArray라는 Tarray를 사용하여 랜덤으로 실행시기킨다.*/
/**또한,  좀비 자신의 Collision을 Off시킨다.*/
void ABaseZombie::Die()
{
	DieAnimationing = true;
	int MinIndex = 0;
	int MaxIndex = SoundArray.Num() - 1;
	int32 Index = FMath::RandRange(MinIndex, MaxIndex);

	if(SoundArray[Index])
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundArray[Index],10.0f,10.0f);
	}
	else
	{
		CLog::Print("Not Sound");
	}

	AMainPlayer* MainPlayer =Cast<AMainPlayer>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if(MainPlayer)
	{
		const int EnemyCount = -1;
		MainPlayer->GetMainHudWidget()->SetEnemyCount(EnemyCount,true);
	}
	GetController()->UnPossess();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ABaseZombie::FinalDeath, 3.0f, false);
}

/**Die 함수에서 어느정도 시간이 지나면 Zombie Actor를 제거한다.*/
void ABaseZombie::FinalDeath()
{
	Destroy();
}

/**플레이어와 닿았을때 BT에서 MeleeAttack함수를 실행하여 Montage를 실행한다.*/
void ABaseZombie::MeleeAttack()
{
	if(Montages&&!DieAnimationing)
	{
		PlayAnimMontage(Montages);
	}
}

/**좀비의 손에 플레이어와 겹치면 데미지를 준다고 판단 Player에게 TakeDamage를 통해 체력을 깍게한다.*/
/**Player가 겹치면서 여러번 맞을수있으니 TArray을 통해 한번 맞으면 Player를 Tarray에 등록한다.*/
void ABaseZombie::OnBeginOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);
	AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
	CheckNull(MainPlayer);
	if (MainPlayers.Num() >= 1)
		return;
	MainPlayers.Add(MainPlayer);
	FDamageEvent e;
	MainPlayer->TakeDamage(10.0f, e, UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void ABaseZombie::OnEndOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

/**좀비의 공격이 끝나면 TArray에 데이터를 지운다.*/
void ABaseZombie::ArrayClear()
{
	MainPlayers.Empty();
}

/**노티파이를 통해 손 Collision을 킨다.*/
void ABaseZombie::CollisionOn()
{
	SphereComponentHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

/**노티파이를 통해 손 Collision을 끈다.*/
void ABaseZombie::CollisionOff()
{
	SphereComponentHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrayClear();
}
