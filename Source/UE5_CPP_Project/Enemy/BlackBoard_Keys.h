#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

/**블랙보드 Key를 담는 헤더파일 namespace로 정의*/
namespace bb_Keys
{
	TCHAR const* const TargetLocation = TEXT("TargetLocation");
	TCHAR const* const CanSeePlayer = TEXT("CanSeePlayer");
	TCHAR const* const PatrolPathVector = TEXT("PatrolPathVector");
	TCHAR const* const PatrolPathIndex = TEXT("PatrolPathIndex");
	TCHAR const* const PlayerIsInMeleeRange = TEXT("PlayerIsInMeleeRange");
	TCHAR const* const ISInvestigating = TEXT("ISInvestigating");
}