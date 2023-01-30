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

	
	CHelpers::GetAsset<UAnimMontage>(&Montages, "AnimMontage'/Game/EnemyZombie/ZombieBase/Animation/Attack/Anim_Monster_Attack_1_Montage.Anim_Monster_Attack_1_Montage'");
	
}

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

}

void ABaseZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

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

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ABaseZombie::FinalDeath, 3.0f, false);
}

void ABaseZombie::FinalDeath()
{
	Destroy();
}

void ABaseZombie::MeleeAttack()
{
	if(Montages)
	{
		PlayAnimMontage(Montages);
	}
}

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

void ABaseZombie::ArrayClear()
{
	MainPlayers.Empty();
}

void ABaseZombie::CollisionOn()
{
	SphereComponentHand->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABaseZombie::CollisionOff()
{
	SphereComponentHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArrayClear();
}
