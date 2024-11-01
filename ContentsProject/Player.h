#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	static APlayer* Ball;

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveFunction(FVector2D _Dir);

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
	
	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();

protected:

private:
	float Speed = 800.0f;
	float radian = 0.f;
	int MySpriteIndex = 0;

	class USpriteRenderer* SpriteRenderer;

	// class std::vector< USpriteRenderer* LeftRenderer;

};

