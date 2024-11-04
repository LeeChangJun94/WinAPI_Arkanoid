#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	~AItem();

	static AItem* Item;

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int ItemType = 0;

protected:

private:
	float Speed = 400.0f;
	class USpriteRenderer* SpriteRenderer1 = nullptr;
	class USpriteRenderer* SpriteRenderer2 = nullptr;
};

