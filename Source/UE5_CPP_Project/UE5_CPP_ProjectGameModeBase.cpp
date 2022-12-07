#include "UE5_CPP_ProjectGameModeBase.h"
#include "Global.h"
AUE5_CPP_ProjectGameModeBase::AUE5_CPP_ProjectGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/MyMainPlayer.MyMainPlayer_C'");
}