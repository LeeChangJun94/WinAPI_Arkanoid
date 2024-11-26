#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

enum class EInOuttro_StarShip
{
	NONE,
	INTRO,
	OUTTRO,
};


// Ό³Έν :
class AInOuttro_StarShip : public AActor
{
public:
	// constrcuter destructer
	AInOuttro_StarShip();
	~AInOuttro_StarShip();

	// delete Function
	AInOuttro_StarShip(const AInOuttro_StarShip& _Other) = delete;
	AInOuttro_StarShip(AInOuttro_StarShip&& _Other) noexcept = delete;
	AInOuttro_StarShip& operator=(const AInOuttro_StarShip& _Other) = delete;
	AInOuttro_StarShip& operator=(AInOuttro_StarShip&& _Other) noexcept = delete;

	USpriteRenderer* GetSpriteRenderer()
	{
		return SpriteRenderer;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInOuttroType(EInOuttro_StarShip _StarShipType)
	{
		StarShipType = _StarShipType;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	EInOuttro_StarShip StarShipType = EInOuttro_StarShip::NONE;
};

