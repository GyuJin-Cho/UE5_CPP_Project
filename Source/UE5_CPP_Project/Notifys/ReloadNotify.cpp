#include "Notifys/ReloadNotify.h"
#include "Global.h"
#include "Player/MainPlayer.h"
FString UReloadNotify::GetNotifyName_Implementation() const
{
	return "Reload";
}

/**재장전 애니메이션 실행중에 장전이 완료되면 총알을 최대치로 장전*/
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
