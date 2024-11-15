#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

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

protected:

private:

	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
};

