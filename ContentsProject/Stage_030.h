#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_030 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_030();
	~AStage_030();

	// delete Function
	AStage_030(const AStage_030& _Other) = delete;
	AStage_030(AStage_030&& _Other) noexcept = delete;
	AStage_030& operator=(const AStage_030& _Other) = delete;
	AStage_030& operator=(AStage_030&& _Other) noexcept = delete;

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

