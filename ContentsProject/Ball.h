#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

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
	void ReStart(float _DeltaTime);
	

	FVector2D GetBallScale()
	{
		return SpriteRenderer->GetComponentScale();
	}

	void SetBallSpeed(float _Speed)
	{
		Speed = _Speed;
	}
	
	//APlayerLife* SetPlayerLife(APlayerLife* _PlayerLife)
	//{
	//	PlayerLife = _PlayerLife;
	//}


protected:

private:
	float Speed = 800.0f;
	float radian = 0.0f;
	float CheckTime = 0.0f;
	bool StartTime = true;

	class APlayerLife* PlayerLife = nullptr;
	class USpriteRenderer* SpriteRenderer;
};

