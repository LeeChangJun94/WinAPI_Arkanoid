#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_010 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_010();
	~AStage_010();

	// delete Function
	AStage_010(const AStage_010& _Other) = delete;
	AStage_010(AStage_010&& _Other) noexcept = delete;
	AStage_010& operator=(const AStage_010& _Other) = delete;
	AStage_010& operator=(AStage_010&& _Other) noexcept = delete;

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

