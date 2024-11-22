#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class APlayer;

// Ό³Έν :
class ABossBullet : public AActor
{
public:
	// constrcuter destructer
	ABossBullet();
	~ABossBullet();

	// delete Function
	ABossBullet(const ABossBullet& _Other) = delete;
	ABossBullet(ABossBullet&& _Other) noexcept = delete;
	ABossBullet& operator=(const ABossBullet& _Other) = delete;
	ABossBullet& operator=(ABossBullet&& _Other) noexcept = delete;

	void Attack();
	//void AttackDone();

	void SetBossBulletDir(FVector2D _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	APlayer* Vaus = nullptr;

	//int AttackCheck = 2;

	FVector2D Dir = { 0.0f, 0.0f };
	float Speed = 300.0f;
};

