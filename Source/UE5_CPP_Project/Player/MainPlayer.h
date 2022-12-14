#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class UE5_CPP_PROJECT_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()
public:
	bool IsSprint;
	bool IsAuto;
	bool IsAim;
	bool IsReload;
	FTimerHandle RifleFireTimer;

	//Components
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	//Widgets
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCrossHair> CrossHairWidgetClass;

	class UCrossHair* CrossHairWidgets;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UMainHudWidget> MainHudWidgetClass;

	class UMainHudWidget* MainHudWidget;

	//Weapon
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class AM4Weapon> M4Weapon;

	class AM4Weapon* M4WeaponActor;

	//Montage
private:
	class UAnimMontage* FireMontage;
	class UAnimMontage* ReloadMontage;
	class UAnimMontage* EmptyFire;
private:
	float AimTargetLength=100.0f;
	float NotAimTargetLength = 300.0f;

	//AI
private:
	class UAIPerceptionStimuliSourceComponent* Stimulus;

public:
	AMainPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ActorComponents
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UStateComponent* State;

public:
	FORCEINLINE bool GetSprint() { return IsSprint; }
	FORCEINLINE bool GetAim() { return IsAim; }
	FORCEINLINE bool GetReload() { return IsReload; }
	FORCEINLINE UStatusComponent* GetStatus() { return Status; }
	FORCEINLINE UStateComponent* GetState() { return State; }
	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void Jump();
	void JumpEnd();
	void Sprint();
	void SprintEnd();
	void Aim();
	void AimEnd();
	void Auto();
	void AutoEnd();
	void Action();
	void ActionEnd();
	void Reload();

	void Fire();

	void Equip();

	// ???????? ????
public:
	void ReloadAction();
	void Recoil();

	//AI
private:
	void SetupStimulus();

};
