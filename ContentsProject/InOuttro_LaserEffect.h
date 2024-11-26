#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

enum class EInOuttro_LaserEffect
{
	NONE,
	INTRO,
	OUTTRO,
};

// Ό³Έν :
class AInOuttro_LaserEffect : public AActor
{
public:
	// constrcuter destructer
	AInOuttro_LaserEffect();
	~AInOuttro_LaserEffect();

	// delete Function
	AInOuttro_LaserEffect(const AInOuttro_LaserEffect& _Other) = delete;
	AInOuttro_LaserEffect(AInOuttro_LaserEffect&& _Other) noexcept = delete;
	AInOuttro_LaserEffect& operator=(const AInOuttro_LaserEffect& _Other) = delete;
	AInOuttro_LaserEffect& operator=(AInOuttro_LaserEffect&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInOuttroType(EInOuttro_LaserEffect _LaserEffectType)
	{
		LaserEffectType = _LaserEffectType;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	EInOuttro_LaserEffect LaserEffectType = EInOuttro_LaserEffect::NONE;
};

