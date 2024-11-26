#pragma once
#include <EngineCore/Actor.h>

class ABall;

enum class BossState
{
	IDLE,
	ATTACK,
	DESTROY,
};

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

	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer1;
	}

	BossState GetCurBossState()
	{
		return CurBossState;
	}

	void ChangeBossState(BossState _CurBossState)
	{
		CurBossState = _CurBossState;
	}

	void SetCountTime(float _CountTime)
	{
		CountTime = _CountTime;
	}

	void Idle(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Destroy(float _DeltaTime);

protected:

private:
	ABall* Ball = nullptr;
	USpriteRenderer* SpriteRenderer1 = nullptr;
	USpriteRenderer* SpriteRenderer2 = nullptr;
	U2DCollision* CollisionComponent = nullptr;

	BossState CurBossState = BossState::IDLE;

	int BossHP = 5;
	float Ratio = 0;
	float Line = 0;
	float CountTime = 0.0f;
	bool BossDeath = false;
	bool BossAttack = true;

	FTransform BallTrans;
	FTransform BossTrans;

};

