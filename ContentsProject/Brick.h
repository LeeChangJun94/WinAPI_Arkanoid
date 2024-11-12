#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>

enum class EReflectionDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX,
};

class ABall;

// ���� :
class ABrick : public AActor
{
public:
	// constrcuter destructer
	ABrick();
	~ABrick();

	// delete Function
	ABrick(const ABrick& _Other) = delete;
	ABrick(ABrick&& _Other) noexcept = delete;
	ABrick& operator=(const ABrick& _Other) = delete;
	ABrick& operator=(ABrick&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetBrickSize(FVector2D _Size)
	{
		SpriteRenderer->SetComponentScale(_Size);
	}



	bool RectCheck();
	EReflectionDir ReflectionDirCheck();

	void SetBallActor(ABall* BallActor)
	{
		this->BallActor = BallActor;
	}

	ABall* GetBallActor()
	{
		return this->BallActor;
	}

protected:

private:
	static FVector2D ReflectionVector[static_cast<int>(EReflectionDir::MAX)];
	
	FTransform BallTrans;

	FTransform BrickTrans;

	USpriteRenderer* SpriteRenderer;

	bool LeftTop = false;
	bool LeftBottom = false;
	bool RightTop = false;
	bool RightBottom = false;


	float Ratio = 0;
	float Line = 0;

	int PlayerScore = 0;

	ABall* BallActor = nullptr;
};

