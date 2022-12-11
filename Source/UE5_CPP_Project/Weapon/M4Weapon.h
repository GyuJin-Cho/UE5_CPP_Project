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
		class UBoxComponent* Box;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return Mesh; }

};
