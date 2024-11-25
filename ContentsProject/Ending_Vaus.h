#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AEnding_Vaus : public AActor
{
public:
	// constrcuter destructer
	AEnding_Vaus();
	~AEnding_Vaus();

	// delete Function
	AEnding_Vaus(const AEnding_Vaus& _Other) = delete;
	AEnding_Vaus(AEnding_Vaus&& _Other) noexcept = delete;
	AEnding_Vaus& operator=(const AEnding_Vaus& _Other) = delete;
	AEnding_Vaus& operator=(AEnding_Vaus&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Distance = { 0, 0 };

	float Speed = 40.0f;


};

