#pragma once
#include <EnginePlatform/EngineSound.h>

class AText;

class AGameOver : public AGameMode
{
public:
	// constrcuter destructer
	AGameOver();
	~AGameOver();

	// delete Function
	AGameOver(const AGameOver& _Other) = delete;
	AGameOver(AGameOver&& _Other) noexcept = delete;
	AGameOver& operator=(const AGameOver& _Other) = delete;
	AGameOver& operator=(AGameOver&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _Deltatime);

protected:

private:
	AText* Text1 = nullptr;
	AText* Text2 = nullptr;
	AText* Text3 = nullptr;
	AText* Text4 = nullptr;
	AText* Text5 = nullptr;
	AText* Text6 = nullptr;
	AText* Text7 = nullptr;
	AText* Text8 = nullptr;
	AText* Text9 = nullptr;

	USoundPlayer GameOverSound;

	int Time = 10;
	float CheckTime = 0.0f;
	bool GameOver = false;

};

