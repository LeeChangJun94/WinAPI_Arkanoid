#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class APlayer;
class APlayerLife;
class U2DCollision;
class USpriteRenderer;

enum class StartLocationType
{
	RIGHT,
	LEFT,
};

// Ό³Έν :
class ABall : public AActor
{
public:
	// constrcuter destructer
	ABall();
	~ABall();

	//static ABall* Ball;

	// delete Function
	ABall(const ABall& _Other) = delete;
	ABall(ABall&& _Other) noexcept = delete;
	ABall& operator=(const ABall& _Other) = delete;
	ABall& operator=(ABall&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void MoveFunction(FVector2D _Dir);

	FVector2D Dir = { 0.f , 0.f };


	void RunSoundPlay();

	void BorderReflect(float _DeltaTime);
	//void ReStart(float _DeltaTime);
	

	FVector2D GetBallScale()
	{
		return SpriteRenderer->GetComponentScale();
	}

	void SetBallSpeed(float _Speed);
	//{
	//	Speed = _Speed;
	//}
	
	FVector2D GetBallDir();
	//{
	//	return Dir;
	//}

	void SetBallDir(FVector2D _Dir);
	//{
	//	Dir = _Dir;
	//}
	//APlayerLife* SetPlayerLife(APlayerLife* _PlayerLife)
	//{
	//	PlayerLife = _PlayerLife;
	//}
	void SetBallDir(float _DIr1, float _Dir2);

	void SetStarTime(bool _StartTime)
	{
		StartTime = _StartTime;
	}

	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

	U2DCollision* GetCollisionComponent()
	{
		return CollisionComponent;
	}

	bool GetBallCatch()
	{
		return BallCatch;
	}

	void SetBallCatch(bool _BallCatch)
	{
		BallCatch = _BallCatch;
	}

	float Distance = 0.0f;
	//float GetBallRadian()
	//{
	//	return Radian;
	//}

	std::list<FVector2D> BallLocationList;

protected:

private:
	float Speed = 500.0f;
	//float Radian = 30.0f;
	float CheckTime = 0.0f;
	bool BallCatch = false;
	bool StartTime = true;

	StartLocationType StartLocation = StartLocationType::RIGHT;
	APlayerLife* PlayerLife = nullptr;
	APlayer* Vaus = nullptr;
	USpriteRenderer* SpriteRenderer;
	U2DCollision* CollisionComponent = nullptr;
};

