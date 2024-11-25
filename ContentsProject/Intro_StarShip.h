#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AIntro_StarShip : public AActor
{
public:
	// constrcuter destructer
	AIntro_StarShip();
	~AIntro_StarShip();

	// delete Function
	AIntro_StarShip(const AIntro_StarShip& _Other) = delete;
	AIntro_StarShip(AIntro_StarShip&& _Other) noexcept = delete;
	AIntro_StarShip& operator=(const AIntro_StarShip& _Other) = delete;
	AIntro_StarShip& operator=(AIntro_StarShip&& _Other) noexcept = delete;

	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;

};

