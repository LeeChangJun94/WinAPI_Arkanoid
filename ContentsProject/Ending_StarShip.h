#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

// Ό³Έν :
class AEnding_StarShip : public AActor
{
public:
	// constrcuter destructer
	AEnding_StarShip();
	~AEnding_StarShip();

	// delete Function
	AEnding_StarShip(const AEnding_StarShip& _Other) = delete;
	AEnding_StarShip(AEnding_StarShip&& _Other) noexcept = delete;
	AEnding_StarShip& operator=(const AEnding_StarShip& _Other) = delete;
	AEnding_StarShip& operator=(AEnding_StarShip&& _Other) noexcept = delete;

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

