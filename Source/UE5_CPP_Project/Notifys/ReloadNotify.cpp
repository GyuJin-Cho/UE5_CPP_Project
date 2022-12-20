#include "Notifys/ReloadNotify.h"
#include "Global.h"
#include "Player/MainPlayer.h"
FString UReloadNotify::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UReloadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AActor* actor = MeshComp->GetOwner();
	AMainPlayer* player = nullptr;

	CheckNull(actor);
	player = Cast<AMainPlayer>(actor);
	CheckNull(player);
	player->ReloadAction();

}
