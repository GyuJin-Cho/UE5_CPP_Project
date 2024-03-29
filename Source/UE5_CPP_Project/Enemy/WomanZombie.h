/**여성형 좀비 좀비베이스를 상속받았다.*/
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
