#include "Player/MainPlayer.h"
#include "Global.h"
#include "Widgets/CrossHair.h"
#include "Widgets/MainHudWidget.h"
#include "Widgets/PauseMenu.h"
#include "Widgets/GameOverClearWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/ArmoComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/M4Weapon.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Controller.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Enemy/AI_Tags.h"
#include "Engine/CollisionProfile.h"
#include "Engine/Engine.h"
#include "Sound/SoundCue.h"
AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SCK_Casual01/Models/Premade_Characters/MESH_PC_02.MESH_PC_02'");
	GetMesh()->SetSkeletalMesh(mesh);
	
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_IK/ABP_MainPlayer.ABP_MainPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.0f);
	GetCapsuleComponent()->SetCapsuleRadius(42.0f);

	//Widgets
	CHelpers::GetClass<UCrossHair>(&CrossHairWidgetClass, "WidgetBlueprint'/Game/Player/Widgets/CrossHair.CrossHair_C'");
	CHelpers::GetClass<UMainHudWidget>(&MainHudWidgetClass, "WidgetBlueprint'/Game/Player/Widgets/MainHudWidget.MainHudWidget_C'");
	CHelpers::GetClass<UPauseMenu>(&PauseMenuWidgetClass, "WidgetBlueprint'/Game/PauseMenu/PauseMenuWidget.PauseMenuWidget_C'");
	CHelpers::GetClass<UGameOverClearWidget>(&GameOverClearWidgetClass, "WidgetBlueprint'/Game/GameOverClearWidgets/GameOverClearWidget_BP.GameOverClearWidget_BP_C'");

	//Montage
	CHelpers::GetAsset<UAnimMontage>(&FireMontage, "AnimMontage'/Game/Player/Animation/Fire/TPP_VG_Fire_Normal_Anim_Montage.TPP_VG_Fire_Normal_Anim_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Player/Animation/Action/TPP_HG_Reload_30Mag_Anim_Montage.TPP_HG_Reload_30Mag_Anim_Montage'");
	CHelpers::GetAsset<UAnimMontage>(&EmptyFire, "AnimMontage'/Game/Player/Animation/Fire/TPP_VG_Fire_Empty_Anim_Montage.TPP_VG_Fire_Empty_Anim_Montage'");

	SetupStimulus();
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	if(CrossHairWidgetClass)
	{
		CrossHairWidgets = CreateWidget<UCrossHair>(GetWorld(), CrossHairWidgetClass);
		CrossHairWidgets->AddToViewport();
		CrossHairWidgets->SetVisibility(ESlateVisibility::Hidden);
	}

	if(MainHudWidgetClass)
	{
		MainHudWidget = CreateWidget<UMainHudWidget>(GetWorld(), MainHudWidgetClass);
		MainHudWidget->AddToViewport();
		MainHudWidget->HealthUpdate(MaxHealth, MaxHealth);
	}

	if(PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuWidgetClass);
		PauseMenuWidget->AddToViewport();
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameOverClearWidgetClass)
	{
		GameOverClearWidget = CreateWidget<UGameOverClearWidget>(GetWorld(), GameOverClearWidgetClass);
		GameOverClearWidget->AddToViewport();
		GameOverClearWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if(M4Weapon)
	{
		FActorSpawnParameters SpawnParameters;
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(M4Weapon,FVector(0.f,0.f,0.f),FRotator(0.f,0.f,0.f), SpawnParameters);
		M4WeaponActor = Cast<AM4Weapon>(SpawnActor);
		MainHudWidget->SetMaxArmo(M4WeaponActor->GetArmo()->GetMaxArmo());
	}

	Equip();
	MainHudWidget->IsAuto(IsAuto);
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &AMainPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &AMainPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMainPlayer::JumpEnd);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMainPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMainPlayer::SprintEnd);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &AMainPlayer::Aim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &AMainPlayer::AimEnd);
	PlayerInputComponent->BindAction("IsAuto", EInputEvent::IE_Pressed, this, &AMainPlayer::Auto);
	PlayerInputComponent->BindAction("IsAuto", EInputEvent::IE_Released, this, &AMainPlayer::AutoEnd);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &AMainPlayer::Action);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Released, this, &AMainPlayer::ActionEnd);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AMainPlayer::Reload);
	PlayerInputComponent->BindAction("PauseMenu", EInputEvent::IE_Pressed, this, &AMainPlayer::PuaseMenuOn).bExecuteWhenPaused = true;
}

void AMainPlayer::OnMoveForward(float InAxis)
{
	if(InAxis<0)
	{
		IsSprint = false;
		Status->SetSpeed(ECharacterSpeed::Run);
		IsBackMoving = true;
	}
	else
	{
		IsBackMoving = false;
	}

	if (State->IsDeadMode())
		return;
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);

}

void AMainPlayer::OnMoveRight(float InAxis)
{
	
	if (State->IsDeadMode())
		return;
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
	

}

void AMainPlayer::OnHorizontalLook(float InAxis)
{
	if (State->IsDeadMode())
		return;
	float rate = 45.0f;
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::OnVerticalLook(float InAxis)
{
	if (State->IsDeadMode())
		return;
	float rate = 45.0f;
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::Jump()
{
	if (State->IsDeadMode())
		return;
	ACharacter::Jump();
}

void AMainPlayer::JumpEnd()
{
	if (State->IsDeadMode())
		return;
	ACharacter::Jump();
}

void AMainPlayer::Sprint()
{
	if (IsBackMoving)
		return;
	if (State->IsDeadMode())
		return;
	if(Status->CanMove())
	{
		IsSprint = true;
		Status->SetSpeed(ECharacterSpeed::Sprint);
	}
	
}

void AMainPlayer::SprintEnd()
{
	if (IsBackMoving)
		return;
	if (State->IsDeadMode())
		return;
	if (Status->CanMove())
	{
		IsSprint = false;
		Status->SetSpeed(ECharacterSpeed::Run);
	}
}

void AMainPlayer::Aim()
{
	if (IsSprint||State->IsDeadMode())
		return;
	CrossHairWidgets->SetVisibility(ESlateVisibility::Visible);
	State->SetAimMode();
	IsAim = true;
	SpringArm->SetRelativeLocation(FVector(-80, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 150.0f;
	Status->SetSpeed(ECharacterSpeed::Walk);
	
}

void AMainPlayer::AimEnd()
{
	if (State->IsDeadMode())
		return;
	if (IsSprint)
		return;
	CrossHairWidgets->SetVisibility(ESlateVisibility::Hidden);
	State->SetIdleMode();
	IsAim = false;
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 300.0f;
	Status->SetSpeed(ECharacterSpeed::Run);
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AMainPlayer::Auto()
{
	if (State->IsDeadMode())
		return;
	if(!State->IsFireMode())
	{
		if(IsAuto)
		{
			IsAuto = false;
			MainHudWidget->IsAuto(IsAuto);
		}
		else
		{
			IsAuto = true;
			MainHudWidget->IsAuto(IsAuto);
		}

	}
}

void AMainPlayer::AutoEnd()
{
}

void AMainPlayer::Action()
{
	if (State->IsDeadMode())
		return;
	if(State->IsAimMode())
	{
		State->SetFireMode();
		Fire();
	}
}

void AMainPlayer::ActionEnd()
{
	if (State->IsDeadMode())
		return;
	if(State->IsFireMode())
	{
		State->SetAimMode();
		if (IsAuto)
			GetWorldTimerManager().ClearTimer(RifleFireTimer);
	}
}

void AMainPlayer::Reload()
{
	if (State->IsDeadMode())
		return;
	if (IsAim)
		return;
	if (IsReload)
		return;
	if(M4WeaponActor->GetArmo()->GetArmo()!= M4WeaponActor->GetArmo()->GetMaxArmo())
	{
		IsReload = true;
		PlayAnimMontage(ReloadMontage);
	}
}

void AMainPlayer::ReloadAction()
{
	if (State->IsDeadMode())
		return;
	IsReload = false;
	MainHudWidget->Reload(M4WeaponActor->GetArmo()->GetMaxArmo());
	M4WeaponActor->SetArmo();
}

void AMainPlayer::Recoil()
{
	float PitchRecoil = 0.5f;
	float YawRecoil = 0.5f;

	float PitchRandom = FMath::RandRange(-1.0f, -0.5f);
	float YawRandom = FMath::RandRange(-0.5f, 0.5f);

	AddControllerPitchInput(PitchRecoil* PitchRandom);
	AddControllerYawInput(YawRecoil * YawRandom);
}

void AMainPlayer::SetupStimulus()
{
	
	CHelpers::CreateActorComponent<UAIPerceptionStimuliSourceComponent>(this,&Stimulus, "Stimulus");
	CheckNull(Stimulus);
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

void AMainPlayer::OnDistract()
{
	if(DistractionSound)
	{
		FVector location = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DistractionSound, location);
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), location, 1.0f, this, 0.0f, tags::noise_tag);
	}
}

void AMainPlayer::Fire()
{
	if (State->IsDeadMode())
		return;
	if (IsReload)
		return;
	if(M4WeaponActor->GetArmo()->GetArmo()!=0)
	{
		if (IsAuto)
		{
			PlayAnimMontage(FireMontage);
			M4WeaponActor->Fire(this);
			GetWorld()->GetTimerManager().SetTimer(RifleFireTimer, this, &AMainPlayer::Fire, 0.1f, false);
		}
		else
		{
			PlayAnimMontage(FireMontage);
			M4WeaponActor->Fire(this);
		}
		MainHudWidget->DecreaseArmo(M4WeaponActor->GetArmo()->GetArmo());
		OnDistract();
	}
	else
	{
		PlayAnimMontage(EmptyFire);
	}
}

void AMainPlayer::Equip()
{
	if (M4WeaponActor)
	{

		M4WeaponActor->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		
		GetMesh()->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RighthandSocket = GetMesh()->GetSocketByName("WeaponSocket");

		if (RighthandSocket)
		{
			RighthandSocket->AttachActor(M4WeaponActor,GetMesh());
		}
	}
}

void AMainPlayer::PuaseMenuOn()
{
	
	if(PauseMenuWidget)
	{
		if (PauseMenuWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(true);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		}
		else
		{
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(false);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		}
	}
	
}

float AMainPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                              AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	if (DieAnimationing)
		return 0.f;
	Health -= DamageAmount;

	MainHudWidget->HealthUpdate(Health, MaxHealth);

	if (Health <= 0)
	{
		Die();
	}

	return DamageAmount;
}

void AMainPlayer::Die()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DieAnimationing = true;
	GameOverClearWidget->SetVisibility(ESlateVisibility::Visible);
	GameOverClearWidget->GameOver();
	if(DeathSound)
		UGameplayStatics::PlaySound2D(GetWorld(), DeathSound, 1.0f, 1.0f);
	State->SetDeadMode();
}

void AMainPlayer::FinalDeath()
{
	//todo
}

void AMainPlayer::Clear()
{
	GameOverClearWidget->SetVisibility(ESlateVisibility::Visible);
	GameOverClearWidget->Clear();
}

