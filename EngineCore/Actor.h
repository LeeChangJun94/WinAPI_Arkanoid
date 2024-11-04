#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineMath.h>

#include "EngineSprite.h"

// ���� :
class AActor : public UObject
{
public:
	typedef AActor Super;

	friend class ULevel;

	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	// ��ŸŸ���̶� �����ΰ�?
	virtual void Tick(float _DeltaTime) {}

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}


	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

	FVector2D GetActorLocation()
	{
		return Transform.Location;
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	//�߰�
	FVector2D GetActorScale()
	{
		return Transform.Scale;
	}

	// ������Ʈ�� �����ڴ� ���� ������ ���Ͱ� �ؾ��Ѵ�.
	// �ٸ� Ŭ������ ����� �����ϸ� �ȵȴ�.
	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);
		// ���� �� ���� �����̾�.
		ComponentPtr->ParentActor = this;

		// �����ɶ� ���� �ʽ��ϴ�.
		// NewComponent->BeginPlay();
		// ����⸸ �ϰ� ���� ���� ���°� �Ȱ�.
		Components.push_back(NewComponent);

		// BeginPlay�� ����ȵ� ������Ʈ���� �� �ڷᱸ���� ��´�.
		ComponentList.push_back(NewComponent);
		return NewComponent;
	}


protected:

private:
	static void ComponentBeginPlay();

	static bool IsNewActorCreate;
	static std::list<class UActorComponent*> ComponentList;

	class ULevel* World = nullptr;

	FTransform Transform;

	std::list<class UActorComponent*> Components;
};
