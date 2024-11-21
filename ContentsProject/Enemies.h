#pragma once

// Ό³Έν :
class AEnemies : public AActor
{
public:
	// constrcuter destructer
	AEnemies();
	~AEnemies();

	// delete Function
	AEnemies(const AEnemies& _Other) = delete;
	AEnemies(AEnemies&& _Other) noexcept = delete;
	AEnemies& operator=(const AEnemies& _Other) = delete;
	AEnemies& operator=(AEnemies&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);
	FVector2D Dir = { 0.f , 0.f };
protected:

private:
	float Speed = 300.0f;

	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
};

