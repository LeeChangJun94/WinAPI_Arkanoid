#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>
#include "Bullet.h"


class U2DCollision;
class APlayerLife;
class ABall;

enum class PlayerState
{
	Create,
	Idle,
	Laser,
	Enlarge,
	Catch,
	Destroy,
};


// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	//static APlayer* Vaus;

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	int GetPlayerScore() const
	{
		return PlayerScore;
	}

	void AddPlayerScore(int _PlayerScore)
	{
		PlayerScore += _PlayerScore;
	}
			
	PlayerState GetCurPlayerState()
	{
		return CurPlayerState;
	}

	FVector2D Dir = { 0.f , 0.f };

	std::list<ABullet*> BulletPtr;

	void LevelChangeStart() override;

	void LevelChangeEnd();

	std::list<ABullet*>& GetBulletPtr()
	{
		return BulletPtr;
	}

	void ChangeState(PlayerState CurPlayerState);

	APlayerLife* GetPlayerLife()
	{
		return PlayerLife;
	}

	void SetPlayerLife(APlayerLife* _PlayerLife)
	{
		PlayerLife = _PlayerLife;
	}

	void SetBall(ABall* _Ball)
	{
		Ball = _Ball;
	}

	U2DCollision* GetCollisionComponent()
	{
		return CollisionComponent;
	}

	bool GetStartSwitch()
	{
		return StartSwitch;
	}

	void SetStartSwitch(bool _StartSwitch)
	{
		StartSwitch = _StartSwitch;
	}

	bool CatchEffect = false;
	bool SlowEffect = false;
	
	static int PlayerScore;

protected:

private:
	float Speed = 300.0f;
	float radian = 0.0f;
	
	int MySpriteIndex = 0;
	int BulletCount = 0;
	class USpriteRenderer* SpriteRenderer = nullptr;

	PlayerState CurPlayerState = PlayerState::Idle;

	APlayerLife* PlayerLife = nullptr;
	ABall* Ball = nullptr;

	FTransform BallTrans;
	FTransform VausTrans;

	USoundPlayer EnlargeSound;
	USoundPlayer LaserSound;
	USoundPlayer Ball_VausSound;
	USoundPlayer VausDeadSound;

	float Ratio = 0;
	float Line = 0;

	bool StartSwitch = true;



	void LaserStart();
	void LaserDone();
	void EnlargeStart();
	void EnlargeDone();
	void DestroyStart();
	void DestroyDone();
	void VausReset();
	void CreateDone();
	
	U2DCollision* CollisionComponent;

	void IdleStart();
	void Idle(float _DeltaTime);

	void Laser(float _DeltaTime);
	void Enlarge(float _DeltaTime);
	void CatchStart();
	void Catch(float _DeltaTime);
};

