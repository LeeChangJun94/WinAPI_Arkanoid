#pragma once
#include <EngineBase/Object.h>

// ���� :
class UActorComponent : public UObject
{
public:
	// ���͸��� ParentActor �����Ҽ� �ְ� �����ϱ� ���ؼ� �Ʒ��� ���� §��.
	friend class AActor;

	// constrcuter destructer
	UActorComponent();
	// ��üȭ ����Ű�� �ϴ¹��� �ϳ�
	virtual ~UActorComponent() = 0;

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	// ��ŸŸ���̶� �����ΰ�?
	virtual void ComponentTick(float _DeltaTime) {}

protected:

private:
	class AActor* ParentActor;
};

