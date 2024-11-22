#pragma once
#include <EngineCore/Actor.h>

class ABall;

class ABoss : public AActor
{
public:
	// constrcuter destructer
	ABoss();
	~ABoss();

	// delete Function
	ABoss(const ABoss& _Other) = delete;
	ABoss(ABoss&& _Other) noexcept = delete;
	ABoss& operator=(const ABoss& _Other) = delete;
	ABoss& operator=(ABoss&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	FVector2D Dir = { 0.f , 0.f };


protected:

private:
	ABall* Ball = nullptr;
	USpriteRenderer* SpriteRenderer1 = nullptr;
	USpriteRenderer* SpriteRenderer2 = nullptr;
	U2DCollision* CollisionComponent = nullptr;

	float Ratio = 0;
	float Line = 0;

	FTransform BallTrans;
	FTransform BossTrans;

};

