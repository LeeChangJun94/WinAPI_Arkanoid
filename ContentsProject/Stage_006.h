#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_006 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_006();
	~AStage_006();

	// delete Function
	AStage_006(const AStage_006& _Other) = delete;
	AStage_006(AStage_006&& _Other) noexcept = delete;
	AStage_006& operator=(const AStage_006& _Other) = delete;
	AStage_006& operator=(AStage_006&& _Other) noexcept = delete;

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

