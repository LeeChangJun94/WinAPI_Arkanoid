#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ABullet : public AActor
{
public:
	// constrcuter destructer
	ABullet();
	~ABullet();

	// delete Function
	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

	void Attack();
	void AttackDone();



protected:
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer;
	U2DCollision* CollisionComponent;
	
	float Speed = 600.0f;
};

