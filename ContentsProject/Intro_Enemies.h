#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AIntro_Enemies : public AActor
{
public:
	// constrcuter destructer
	AIntro_Enemies();
	~AIntro_Enemies();

	// delete Function
	AIntro_Enemies(const AIntro_Enemies& _Other) = delete;
	AIntro_Enemies(AIntro_Enemies&& _Other) noexcept = delete;
	AIntro_Enemies& operator=(const AIntro_Enemies& _Other) = delete;
	AIntro_Enemies& operator=(AIntro_Enemies&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;

	FVector2D Bezier = { 0, 0 };

	FVector2D P0 = { 333, 126 };
	FVector2D P1 = { 750, 70 };
	FVector2D P2 = { 750, 750 };
	FVector2D P3 = { 60, 200 };

	float CheckTime = 0.0f;
};

