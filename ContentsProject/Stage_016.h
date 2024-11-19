#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_016 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_016();
	~AStage_016();

	// delete Function
	AStage_016(const AStage_016& _Other) = delete;
	AStage_016(AStage_016&& _Other) noexcept = delete;
	AStage_016& operator=(const AStage_016& _Other) = delete;
	AStage_016& operator=(AStage_016&& _Other) noexcept = delete;

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

