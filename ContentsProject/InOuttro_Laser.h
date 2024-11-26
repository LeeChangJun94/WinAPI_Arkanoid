#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AInOuttro_StarShip;

enum class EInOuttro_Laser
{
	NONE,
	INTRO,
	OUTTRO,
};

// Ό³Έν :
class AInOuttro_Laser : public AActor
{
public:
	// constrcuter destructer
	AInOuttro_Laser();
	~AInOuttro_Laser();

	// delete Function
	AInOuttro_Laser(const AInOuttro_Laser& _Other) = delete;
	AInOuttro_Laser(AInOuttro_Laser&& _Other) noexcept = delete;
	AInOuttro_Laser& operator=(const AInOuttro_Laser& _Other) = delete;
	AInOuttro_Laser& operator=(AInOuttro_Laser&& _Other) noexcept = delete;

	void SetStarShip(AInOuttro_StarShip* _StarShip)
	{
		StarShip = _StarShip;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInOuttroType(EInOuttro_Laser _LaserType)
	{
		LaserType = _LaserType;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	AInOuttro_StarShip* StarShip = nullptr;
	EInOuttro_Laser LaserType = EInOuttro_Laser::NONE;
};

