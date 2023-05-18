/**남성형 좀비 BaseZombie를 상속받음*/
#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseZombie.h"
#include "ManZombie.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AManZombie : public ABaseZombie
{
	GENERATED_BODY()
public:
	AManZombie();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
