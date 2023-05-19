#include "Notifys/RecoilNotify.h"
#include "Global.h"
#include "Player/MainPlayer.h"
FString URecoilNotify::GetNotifyName_Implementation() const
{
	return "RecoilName";
}
/**Notify 총을 발포하는 애니메이션에서 Notify를 등록해 Recoil 함수를 호출*/
void URecoilNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	AActor* actor = MeshComp->GetOwner();
	AMainPlayer* player = nullptr;

	CheckNull(actor);
	player = Cast<AMainPlayer>(actor);
	CheckNull(player);
	player->Recoil();
}
