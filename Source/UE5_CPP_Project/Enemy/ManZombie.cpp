#include "Enemy/ManZombie.h"

AManZombie::AManZombie() : ABaseZombie()
{
	
}

void AManZombie::BeginPlay()
{
	Super::BeginPlay();
}

void AManZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AManZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
