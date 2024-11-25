#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AIntro_Vaus : public AActor
{
public:
	// constrcuter destructer
	AIntro_Vaus();
	~AIntro_Vaus();

	// delete Function
	AIntro_Vaus(const AIntro_Vaus& _Other) = delete;
	AIntro_Vaus(AIntro_Vaus&& _Other) noexcept = delete;
	AIntro_Vaus& operator=(const AIntro_Vaus& _Other) = delete;
	AIntro_Vaus& operator=(AIntro_Vaus&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Distance = { 0, 0 };

	float Speed = 40.0f;


};

