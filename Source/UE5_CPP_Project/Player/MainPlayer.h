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
	bool IsAim;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCrossHair> CrossHairWidgetClass;

	class UCrossHair* CrossHairWidgets;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UMainHudWidget> MainHudWidgetClass;

	class UMainHudWidget* MainHudWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class AM4Weapon> M4Weapon;

	class AM4Weapon* M4WeaponActor;

private:
	float AimTargetLength=100.0f;
	float NotAimTargetLength = 300.0f;
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

public:
	FORCEINLINE bool GetSprint() { return IsSprint; }
	FORCEINLINE bool GetAim() { return IsAim; }
	FORCEINLINE UStatusComponent* GetStatus() { return Status; }
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
	void Equip();


};
