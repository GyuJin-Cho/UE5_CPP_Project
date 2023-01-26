#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h"
#include "CombatInterface.h"
#include "BaseZombie.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API ABaseZombie : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseZombie();

	//State
private:
	bool DieAnimationing;
	FTimerHandle DeathTimer;
	
public:
	UPROPERTY(EditAnywhere, Category = "HP");
		int Health = 100;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* HitParticle;
	class USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UAnimInstance> AnimInstance;
	UPROPERTY(EditAnywhere, Category = "SoundCueArray")
		TArray<class USoundCue*> SoundArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* Montages;
	int MontageIndex = 0;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE bool GetDie() { return DieAnimationing; }
	FORCEINLINE APatrolPath* GetPatrolPath() { return PatrolPath; }
	FORCEINLINE UAnimMontage* GetMontage() { return Montages; }
	FORCEINLINE int GetMontageIndex() { return MontageIndex; }
public:
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void Die();
	void FinalDeath();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	//	int melee_attack();

	int melee_attack_Implementation() override;

public:
	UFUNCTION()
		void OnBeginOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ArrayClear();
	void CollisionOn();
	void CollisionOff();
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta =(AllowPrivateAccess = "true"))
		class APatrolPath* PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponentHand;

	TArray<class AMainPlayer*> MainPlayers;
};
