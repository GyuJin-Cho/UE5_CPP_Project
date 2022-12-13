#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M4Weapon.generated.h"


UCLASS()
class UE5_CPP_PROJECT_API AM4Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AM4Weapon();

private:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Muzzle;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* ShellEject;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Particle;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class AM4Projectile> ProjectileActorClass;

	class AM4Projectile* ProjectileActor;

private:
	UPROPERTY(EditAnywhere)
		class UAnimationAsset* FireAnimation;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Fire(class AMainPlayer* Player);

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return Mesh; }

};
