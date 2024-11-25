#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class AIntro_StarShip;

// Ό³Έν :
class AIntro_Laser : public AActor
{
public:
	// constrcuter destructer
	AIntro_Laser();
	~AIntro_Laser();

	// delete Function
	AIntro_Laser(const AIntro_Laser& _Other) = delete;
	AIntro_Laser(AIntro_Laser&& _Other) noexcept = delete;
	AIntro_Laser& operator=(const AIntro_Laser& _Other) = delete;
	AIntro_Laser& operator=(AIntro_Laser&& _Other) noexcept = delete;

	void SetStarShip(AIntro_StarShip* _StarShip)
	{
		StarShip = _StarShip;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	AIntro_StarShip* StarShip = nullptr;

};

