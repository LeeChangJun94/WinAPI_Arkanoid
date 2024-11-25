#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ABall;
class USpriteRenderer;
class U2DCollision;

// Ό³Έν :
class ADeathLine : public AActor
{
public:
	// constrcuter destructer
	ADeathLine();
	~ADeathLine();

	// delete Function
	ADeathLine(const ADeathLine& _Other) = delete;
	ADeathLine(ADeathLine&& _Other) noexcept = delete;
	ADeathLine& operator=(const ADeathLine& _Other) = delete;
	ADeathLine& operator=(ADeathLine&& _Other) noexcept = delete;

	U2DCollision* GetCollisionComponent()
	{
		return CollisionComponent;
	}

	//ABall* GetCollisionCheck();

protected:

private:

	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
};

