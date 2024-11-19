#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_004 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_004();
	~AStage_004();

	// delete Function
	AStage_004(const AStage_004& _Other) = delete;
	AStage_004(AStage_004&& _Other) noexcept = delete;
	AStage_004& operator=(const AStage_004& _Other) = delete;
	AStage_004& operator=(AStage_004&& _Other) noexcept = delete;

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

