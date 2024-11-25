#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AIntro_LaserEffect : public AActor
{
public:
	// constrcuter destructer
	AIntro_LaserEffect();
	~AIntro_LaserEffect();

	// delete Function
	AIntro_LaserEffect(const AIntro_LaserEffect& _Other) = delete;
	AIntro_LaserEffect(AIntro_LaserEffect&& _Other) noexcept = delete;
	AIntro_LaserEffect& operator=(const AIntro_LaserEffect& _Other) = delete;
	AIntro_LaserEffect& operator=(AIntro_LaserEffect&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;

};

