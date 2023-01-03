#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseZombie.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API ABaseZombie : public ACharacter
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
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE bool GetDie() { return DieAnimationing; }

public:
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void Die();
	void FinalDeath();
};
