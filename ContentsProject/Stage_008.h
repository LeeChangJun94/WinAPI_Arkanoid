#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_008 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_008();
	~AStage_008();

	// delete Function
	AStage_008(const AStage_008& _Other) = delete;
	AStage_008(AStage_008&& _Other) noexcept = delete;
	AStage_008& operator=(const AStage_008& _Other) = delete;
	AStage_008& operator=(AStage_008&& _Other) noexcept = delete;

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

