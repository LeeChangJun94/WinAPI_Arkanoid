#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_025 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_025();
	~AStage_025();

	// delete Function
	AStage_025(const AStage_025& _Other) = delete;
	AStage_025(AStage_025&& _Other) noexcept = delete;
	AStage_025& operator=(const AStage_025& _Other) = delete;
	AStage_025& operator=(AStage_025&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	void LoadBrick(std::string _Stage, APlayerLife* _PlayerLifeActor);

	std::list<ABrick*> BrickPtr;

protected:

private:
	APlayer* Vaus = nullptr;
	std::vector<std::vector<ABrick*>> Bricks;
	USoundPlayer BGMPlayer;

};

