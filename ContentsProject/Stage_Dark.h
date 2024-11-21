#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_Dark : public AGameMode
{
public:
	// constrcuter destructer
	AStage_Dark();
	~AStage_Dark();

	// delete Function
	AStage_Dark(const AStage_Dark& _Other) = delete;
	AStage_Dark(AStage_Dark&& _Other) noexcept = delete;
	AStage_Dark& operator=(const AStage_Dark& _Other) = delete;
	AStage_Dark& operator=(AStage_Dark&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

protected:

private:
	APlayer* Vaus = nullptr;
};

