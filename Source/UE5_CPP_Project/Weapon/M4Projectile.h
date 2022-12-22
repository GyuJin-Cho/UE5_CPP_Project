#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M4Projectile.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AM4Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AM4Projectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;


};
