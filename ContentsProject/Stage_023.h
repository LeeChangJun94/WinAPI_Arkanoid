#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_023 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_023();
	~AStage_023();

	// delete Function
	AStage_023(const AStage_023& _Other) = delete;
	AStage_023(AStage_023&& _Other) noexcept = delete;
	AStage_023& operator=(const AStage_023& _Other) = delete;
	AStage_023& operator=(AStage_023&& _Other) noexcept = delete;

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

