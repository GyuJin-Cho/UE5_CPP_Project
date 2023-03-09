#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseZombie.h"
#include "WomanZombie.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AWomanZombie : public ABaseZombie
{
	GENERATED_BODY()
public:
	AWomanZombie();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
