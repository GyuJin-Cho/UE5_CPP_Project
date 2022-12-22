#include "Weapon/M4Weapon.h"
#include "Global.h"
#include "Player/MainPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArmoComponent.h"
#include "Animation/AnimationAsset.h"
#include "Camera/CameraComponent.h"
#include "Weapon/M4Projectile.h"
#include "Engine/World.h"
AM4Weapon::AM4Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Mesh, "M4", GetRootComponent());
	CHelpers::CreateComponent(this, &Muzzle, "Muzzle", Mesh);
	CHelpers::CreateComponent(this, &ShellEject, "ShellEject", Mesh);
	CHelpers::CreateActorComponent(this, &Armo, "Armo");

	Muzzle->SetRelativeLocation(FVector(0.0f, 55.555556f, 6.896552f));
	Muzzle->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	CHelpers::GetAsset<UAnimationAsset>(&FireAnimation, "AnimSequence'/Game/M4A4_Animated/Gun/Gun_Animations/Gun_Fire.Gun_Fire'");
	CHelpers::GetClass<AM4Projectile>(&ProjectileActorClass, "Blueprint'/Game/Player/Weapon/M4Projectile.M4Projectile_C'");
}

void AM4Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AM4Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AM4Weapon::Fire(AMainPlayer* Player)
{
	//Mesh->PlayAnimation(FireAnimation,false);

	if(Armo->GetArmo()!=0)
	{
		ShellEject->Activate(true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Muzzle->GetComponentLocation(), FRotator(0.0f), FVector(1.3f, 1.3f, 1.3f), false);
		Mesh->PlayAnimation(FireAnimation, false);

		FVector CameraLocation = Player->GetCamera()->GetComponentLocation();
		FVector CameraForward = Player->GetCamera()->GetForwardVector() * 50000.0f;
		FTransform CameraWorldTransForm = Player->GetCamera()->GetComponentTransform();
		FHitResult Result;
		GetWorld()->SpawnActor<AM4Projectile>(ProjectileActorClass, CameraWorldTransForm);

		//if(GetWorld()->LineTraceSingleByChannel(Result, CameraLocation, CameraForward + CameraLocation, ECollisionChannel::ECC_Visibility))
		//{
		//	Result
		//
		//
		//}
		//else
		//{
		//	return;
		//}
		
		Armo->SetArmo(Armo->GetArmo() - 1);
	}
	
}

void AM4Weapon::SetArmo()
{
	Armo->SetArmo(Armo->GetMaxArmo());
}

//void AM4Weapon::Equip(AMainPlayer* Player)
//{
//	
//}