#pragma once
#include <EngineCore/GameMode.h>

class APlayMap;
class AInOuttro_StarShip;
class AText;

// Ό³Έν :
class AOuttro : public AGameMode
{
public:
	// constrcuter destructer
	AOuttro();
	~AOuttro();

	// delete Function
	AOuttro(const AOuttro& _Other) = delete;
	AOuttro(AOuttro&& _Other) noexcept = delete;
	AOuttro& operator=(const AOuttro& _Other) = delete;
	AOuttro& operator=(AOuttro&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayMap* Map = nullptr;
	AInOuttro_StarShip* StarShip = nullptr;

	AText* Text1 = nullptr;
	AText* Text2 = nullptr;
	AText* Text3 = nullptr;
	AText* Text4 = nullptr;
	AText* Text5 = nullptr;
	AText* Text6 = nullptr;
	AText* Text7 = nullptr;
	AText* Text8 = nullptr;
	AText* Text9 = nullptr;




	float CheckTime = 0.0f;
};

