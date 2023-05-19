/**CHelpers Class*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

class UE5_CPP_PROJECT_API CHelpers
{
public:
	/**Asset을 가져오는 함수 더블 포인터로 가져올때 인자로 포인터 변수 하나만 넣으면된다.*/
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Asset Not Found");
		
		*OutObject = asset.Object;
	}

	/**외부 및 파일 이름 사양을 사용하여 문자열 이름으로 개체를 찾거나 로드함 */
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(!!obj, L"Asset Not Found(Dynamic)");

		*OutObject = obj;
	}

	/**Class를 가져오는 함수 보통 BP를 가져올때 사용한다.*/
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass ,FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Class Not Found");
		
		*OutClass = asset.Class;
	}

	/**Component 를 액터에 부착할때 사용되는 함수*/
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);
			return;
		}

		
		InActor->SetRootComponent(*OutComponent);
	}

	/**소켓에 컴포넌트를 부착할때 사용되는 함수 보통 Skeletal Mesh 에 SocketName을 이용하여 부착한다.*/
	template<typename T>
	static void CreateComponentSocket(AActor* InActor, T** OutComponent, FName InName, FName InSocketName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent, InSocketName);
			return;
		}


		InActor->SetRootComponent(*OutComponent);
	}

	/**ActorComponent를 부착할때 사용*/
	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	/**Component를 가져올때 사용한다.*/
	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

};

