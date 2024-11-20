#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ABall;
class USpriteRenderer;
class U2DCollision;

// Ό³Έν :
class ADethLine : public AActor
{
public:
	// constrcuter destructer
	ADethLine();
	~ADethLine();

	// delete Function
	ADethLine(const ADethLine& _Other) = delete;
	ADethLine(ADethLine&& _Other) noexcept = delete;
	ADethLine& operator=(const ADethLine& _Other) = delete;
	ADethLine& operator=(ADethLine&& _Other) noexcept = delete;

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

