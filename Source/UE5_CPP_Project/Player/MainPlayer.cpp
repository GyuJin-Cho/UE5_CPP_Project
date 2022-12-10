#include "Player/MainPlayer.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);

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
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AMainPlayer::OnMoveForward(float InAxis)
{

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);

}

void AMainPlayer::OnMoveRight(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
	

}

void AMainPlayer::OnHorizontalLook(float InAxis)
{
	float rate = 45.0f;
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::OnVerticalLook(float InAxis)
{
	float rate = 45.0f;
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::Jump()
{
	ACharacter::Jump();
}

void AMainPlayer::JumpEnd()
{
	ACharacter::Jump();
}

void AMainPlayer::Sprint()
{
	IsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AMainPlayer::SprintEnd()
{
	IsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

