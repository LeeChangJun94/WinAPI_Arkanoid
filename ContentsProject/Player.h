#pragma once
#include <EngineCore/Actor.h>
#include "Bullet.h"

enum class PlayerState
{
	Create,
	Idle,
	Laser,
	Enlarge,
	Catch,
};


// ���� :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	static APlayer* Vaus;

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
	//void MoveFunction(FVector2D _Dir);

	//void LeftMove(float _DeltaTime);
	//void RightMove(float _DeltaTime);
	//void UpMove(float _DeltaTime);
	//void DownMove(float _DeltaTime);

	//void Normalize(FVector2D& _Vector)
	//{
	//	_Vector.X * _Vector.X;
	//	_Vector.Y * _Vector.Y;
	//	float Sqrt = std::sqrt(_Vector.X * _Vector.X + _Vector.Y * _Vector.Y);
	//	_Vector.X = _Vector.X / Sqrt;
	//	_Vector.Y = _Vector.Y / Sqrt;
	//}
		
	FVector2D Dir = { 0.f , 0.f };

	std::list<ABullet*> BulletPtr;

	void RunSoundPlay();

	void LevelChangeStart() override;

	void LevelChangeEnd();

	std::list<ABullet*>& GetBulletPtr()
	{
		return BulletPtr;;
	}

protected:

private:
	float Speed = 300.0f;
	float radian = 0.f;
	int MySpriteIndex = 0;
	//bool IsTransformEnd = false;

	class USpriteRenderer* SpriteRenderer = nullptr;

	PlayerState CurPlayerState = PlayerState::Idle;

	void ChangeState(PlayerState CurPlayerState);

	FTransform BallTrans;
	FTransform VausTrans;

	float Ratio = 0;
	float Line = 0;

	int PlayerScore = 0;

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
	//inline void AnimationEnd() { IsTransformEnd = true; }
	// class std::vector< USpriteRenderer* LeftRenderer;

	//PlayerState CurPlayerState = PlayerState::Idle;

	//// ����
	//// ����
	//// ��������
	//// 

	//void ChangeState(PlayerState CurPlayerState);

	//void IdleStart();
	//void Idle(float _DeltaTime);
	//void MoveStart();
	//void Move(float _DeltaTime);
	//void Fly(float _DeltaTime);

	//// ���´� �ƴ����� �����̳� üũ�� ó���Ǵ� �Լ�
	//void Gravity()
	//{

	//}


	//// void Jump();


};

