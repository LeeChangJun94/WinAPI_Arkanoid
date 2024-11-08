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

// Ό³Έν :
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

protected:

private:
	static FVector2D ReflectionVector[static_cast<int>(EReflectionDir::MAX)];
	
	FTransform BallTrans;

	FTransform BrickTrans;

	USpriteRenderer* SpriteRenderer;

	float Ratio = 0;
	float Line = 0;

	int PlayerScore = 0;
};

