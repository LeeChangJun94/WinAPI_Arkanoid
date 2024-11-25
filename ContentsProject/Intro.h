#pragma once
#include <EngineCore/GameMode.h>

class APlayMap;
class AText;

// Ό³Έν :
class AIntro : public AGameMode
{
public:
	// constrcuter destructer
	AIntro();
	~AIntro();

	// delete Function
	AIntro(const AIntro& _Other) = delete;
	AIntro(AIntro&& _Other) noexcept = delete;
	AIntro& operator=(const AIntro& _Other) = delete;
	AIntro& operator=(AIntro&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	APlayMap* Map = nullptr;
	AText* Text1 = nullptr;
	AText* Text2 = nullptr;
	AText* Text3 = nullptr;
	AText* Text4 = nullptr;
	AText* Text5 = nullptr;
	AText* Text6 = nullptr;




	float CheckTime = 0.0f;
};

