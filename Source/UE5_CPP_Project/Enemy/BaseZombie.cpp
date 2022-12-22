#include "Enemy/BaseZombie.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseZombie::ABaseZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/EnemyZombie/ZombieBase/Mesh/BaseZombieA01.BaseZombieA01'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/EnemyZombie/ZombieBase/ABP/ABP_ZombieBase.ABP_ZombieBase_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

}

void ABaseZombie::BeginPlay()
{
	Super::BeginPlay();
	
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

	if(Health<=0)
	{
		Die();
	}
	

	return DamageAmount;
}

void ABaseZombie::Die()
{
	DieAnimationing = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ABaseZombie::FinalDeath, 3.0f, false);
}

void ABaseZombie::FinalDeath()
{
	Destroy();
}
