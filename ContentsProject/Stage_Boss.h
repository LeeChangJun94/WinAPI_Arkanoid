#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

class APlayer;

// Ό³Έν :
class AStage_Boss : public AGameMode
{
public:
	// constrcuter destructer
	AStage_Boss();
	~AStage_Boss();

	// delete Function
	AStage_Boss(const AStage_Boss& _Other) = delete;
	AStage_Boss(AStage_Boss&& _Other) noexcept = delete;
	AStage_Boss& operator=(const AStage_Boss& _Other) = delete;
	AStage_Boss& operator=(AStage_Boss&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:
	APlayer* Vaus = nullptr;
	USoundPlayer BGMPlayer;
};

