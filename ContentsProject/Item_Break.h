#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AItem_Break : public AActor
{
public:
	// constrcuter destructer
	AItem_Break();
	~AItem_Break();

	// delete Function
	AItem_Break(const AItem_Break& _Other) = delete;
	AItem_Break(AItem_Break&& _Other) noexcept = delete;
	AItem_Break& operator=(const AItem_Break& _Other) = delete;
	AItem_Break& operator=(AItem_Break&& _Other) noexcept = delete;

protected:

private:
	UEngineSprite* SpriteRenderer = nullptr;


};

