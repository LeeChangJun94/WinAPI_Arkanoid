#pragma once
#include <EngineCore/GameMode.h>

class APlayMap;
class AEnding_StarShip;
class AText;

// Ό³Έν :
class AEnding : public AGameMode
{
public:
	// constrcuter destructer
	AEnding();
	~AEnding();

	// delete Function
	AEnding(const AEnding& _Other) = delete;
	AEnding(AEnding&& _Other) noexcept = delete;
	AEnding& operator=(const AEnding& _Other) = delete;
	AEnding& operator=(AEnding&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayMap* Map = nullptr;
	AEnding_StarShip* Intro_StarShip = nullptr;

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

