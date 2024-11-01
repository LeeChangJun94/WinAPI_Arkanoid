#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>

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


protected:

private:
	
	FTransform BallTrans;
	int BallX = 0;
	int BallY = 0;
	int BallScaleX = 0;
	int BallScaleY = 0;

	FTransform BrickTrans;
	int BrickX = 0;
	int BrickY = 0;
	int BrickScaleX = 0;
	int BrickScaleY = 0;

	USpriteRenderer* SpriteRenderer;

	float Ratio = 0;
	float Line = 0;
};

