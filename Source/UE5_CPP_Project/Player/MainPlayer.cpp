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

/**Player 에 생성자 CDO를 통해 Component 및 Asset등을 가져오는 작업을 한다.*/
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

/**게임이 시작되면 초기화 해줄 함수 위젯과 무기 장착을 주로 해준다.*/
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

/**플레이어 캐릭터에 키 입력을 등록하는 함수입니다. 액션, 축 입력이 있습니다.*/
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

/**앞 뒤 움직을 담당하는 함수입니다. 뒤로 움직임이 있을경우 뛰질 못하고 죽으면 움직이 못하게 막았습니다.*/
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

/**좌 우 움직이는 함수입니다. 똑같이 죽으면 움직이지 못하게 만들었습니다.*/
void AMainPlayer::OnMoveRight(float InAxis)
{
	
	if (State->IsDeadMode())
		return;
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
	

}

/**수평 움직임을 담당하는 함수입니다. 마우스 좌 우를 이동할때마다 Yaw의 방향을 변경합니다.*/
void AMainPlayer::OnHorizontalLook(float InAxis)
{
	if (State->IsDeadMode())
		return;
	float rate = 45.0f;
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

/**수직 움직임을 담당하는 함수입니다. 마우스가 위 아래를 이동할때마다 Pitch의 방향을 변경합니다.*/
void AMainPlayer::OnVerticalLook(float InAxis)
{
	if (State->IsDeadMode())
		return;
	float rate = 45.0f;
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

/**Jump 함수입니다 Space를 사용합니다.*/
void AMainPlayer::Jump()
{
	if (State->IsDeadMode())
		return;
	ACharacter::Jump();
}

/**Jump가 끝날때 있는 함수입니다.*/
void AMainPlayer::JumpEnd()
{
	if (State->IsDeadMode())
		return;
	ACharacter::Jump();
}

/**Shift 키를 눌러 Sprint 모드로 변경해줍니다. 조준모드, 죽을때, 뒤로 걸을때 사용이 불가능 하며 Status를 통해 속도를 600으로 만들어줍니다.*/
void AMainPlayer::Sprint()
{
	if (IsBackMoving)
		return;
	if (State->IsDeadMode())
		return;
	if (State->IsAimMode())
		return;
	if(Status->CanMove())
	{
		IsSprint = true;
		Status->SetSpeed(ECharacterSpeed::Sprint);
	}
	
}

/**Sprint 모드를 종료했을때 다시 속도 400으로 변경해줍니다.*/
void AMainPlayer::SprintEnd()
{
	if (IsBackMoving)
		return;
	if (State->IsDeadMode())
		return;
	if (State->IsAimMode())
		return;
	if (Status->CanMove())
	{
		IsSprint = false;
		Status->SetSpeed(ECharacterSpeed::Run);
	}
}

/**Aim 함수 사용자가 오른쪽 마우스 버튼을 누르고있으면 작동*/
/**SpringArm을 앞으로 땡기고 CrossHairWidget을 Visible상태로 만들어 사격 준비 태세를 한다.*/
/**Spring Arm을 앞으로 땡기면 그 자식 Component인 카메라도 같이 앞으로 땡겨진다.*/
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

/**Aim을 끄는 함수 마우스 오른쪽 버튼을 풀면 꺼진다.*/
/**그럼 SpringArm은 다시 원상태로 돌아온다.*/
/**Spring Arm을 다시 원상태로 돌리면 그 자식 Component인 카메라도 같이 원상태로 돌아온다.*/
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

/**B키를 눌러 총을 연발 및 단발로 변경하는 함수*/
/**MainHud에 Auto Single 이라는 단어로 표현*/
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

/**마우스 왼쪽 클릭할때 총을 발포하는 함수 Aim모드가 켜져있어야 활성화*/
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

/**마우스 왼쪽을 땔떼 활성화되는 함수 RifleFireTimer는 만약 연사 모드일경우 Timer를 설정해놓은것을 Clear해줘야한다.*/
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

/**Reload 함수 R키를 누르고 재장전을 시도한다. 만약 총알이 가득차있는데 재장전을 시도하면 애니메이션이 재생이 안된다.*/
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

/**Notify를 통해 탄창이 총에 장착되는 순간 함수를 실행하여 총알을 끝까지 채운다.*/
void AMainPlayer::ReloadAction()
{
	if (State->IsDeadMode())
		return;
	IsReload = false;
	MainHudWidget->Reload(M4WeaponActor->GetArmo()->GetMaxArmo());
	M4WeaponActor->SetArmo();
}

/**총알의 반동 총을 발포할때마다 랜덤으로 Pitch와 Yaw를 올리거나 내린다.*/
void AMainPlayer::Recoil()
{
	float PitchRecoil = 0.5f;
	float YawRecoil = 0.5f;

	float PitchRandom = FMath::RandRange(-1.0f, -0.5f);
	float YawRandom = FMath::RandRange(-0.5f, 0.5f);

	AddControllerPitchInput(PitchRecoil* PitchRandom);
	AddControllerYawInput(YawRecoil * YawRandom);
}

/**Zombie에 AI가 Player에게 반응해도록 설정하는 함수*/
void AMainPlayer::SetupStimulus()
{
	
	CHelpers::CreateActorComponent<UAIPerceptionStimuliSourceComponent>(this,&Stimulus, "Stimulus");
	CheckNull(Stimulus);
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

/**Zombie가 총의 사운드를 들었을때 반응하도록 만드는 함수*/
void AMainPlayer::OnDistract()
{
	if(DistractionSound)
	{
		FVector location = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DistractionSound, location);
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), location, 1.0f, this, 0.0f, tags::noise_tag);
	}
}

/**실질적인 총을 발포하는 함수 연발일 경우 Timer를 설정하여 0.1초마다 재귀함수를 통해 계속 발포하게 만듬*/
/**또한 OnDistract를 호출하여 좀비가 반응하도록 설정*/
/**m4Weapon이라는 총에 Fire함수를 호출하고 Argument로 자기자신인 this를 넘겨줌*/
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

/**무기 장착 Player Skeletal Mesh 안에 소켓을 만들어 장착한다.*/
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

/**ESC를 눌러 일시정지후 Pause Menu를 부른다.*/
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

/**좀비에게 데미지를 입으면 활성화되는 함수 좀비에 공격력 만큼 체력을 감소시킨다.*/
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

/**Die 함수 죽음과 동시에 Game Over Widget을 Visible 해주고 죽는 소리를 실행한다.*/
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

/**최종적으로 게임을 완수했을때 실행되는 함수*/
void AMainPlayer::Clear()
{
	GameOverClearWidget->SetVisibility(ESlateVisibility::Visible);
	GameOverClearWidget->Clear();
}

