/**CLogClass 게임상에 디스플레이에 출력을 원하거나 Log를찍기위해 편하게 만듬 */
#pragma once

#include "CoreMinimal.h"

#define PrintLine(){ CLog::Log(__FUNCTION__, __LINE__); }

class UE5_CPP_PROJECT_API CLog
{
public:
	static void Print(int32 InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Orange);
	static void Print(float InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Orange);
	static void Print(const FString& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Orange);
	static void Print(const FVector& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Orange);
	static void Print(const FRotator& InValue, int32 InKey = -1, float InDuration = 10.0f, FColor InColor = FColor::Orange);

	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InOjbect);
	static void Log(const FString& InFuncName, int32 InLineNumber);


};
