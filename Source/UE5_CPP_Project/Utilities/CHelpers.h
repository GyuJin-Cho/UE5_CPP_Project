/**CHelpers Class*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

class UE5_CPP_PROJECT_API CHelpers
{
public:
	/**Asset�� �������� �Լ� ���� �����ͷ� �����ö� ���ڷ� ������ ���� �ϳ��� ������ȴ�.*/
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Asset Not Found");
		
		*OutObject = asset.Object;
	}

	/**�ܺ� �� ���� �̸� ����� ����Ͽ� ���ڿ� �̸����� ��ü�� ã�ų� �ε��� */
	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(!!obj, L"Asset Not Found(Dynamic)");

		*OutObject = obj;
	}

	/**Class�� �������� �Լ� ���� BP�� �����ö� ����Ѵ�.*/
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass ,FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Class Not Found");
		
		*OutClass = asset.Class;
	}

	/**Component �� ���Ϳ� �����Ҷ� ���Ǵ� �Լ�*/
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

	/**���Ͽ� ������Ʈ�� �����Ҷ� ���Ǵ� �Լ� ���� Skeletal Mesh �� SocketName�� �̿��Ͽ� �����Ѵ�.*/
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

	/**ActorComponent�� �����Ҷ� ���*/
	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	/**Component�� �����ö� ����Ѵ�.*/
	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

};

