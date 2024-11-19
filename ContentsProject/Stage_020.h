#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_020 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_020();
	~AStage_020();

	// delete Function
	AStage_020(const AStage_020& _Other) = delete;
	AStage_020(AStage_020&& _Other) noexcept = delete;
	AStage_020& operator=(const AStage_020& _Other) = delete;
	AStage_020& operator=(AStage_020&& _Other) noexcept = delete;

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

