#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_007 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_007();
	~AStage_007();

	// delete Function
	AStage_007(const AStage_007& _Other) = delete;
	AStage_007(AStage_007&& _Other) noexcept = delete;
	AStage_007& operator=(const AStage_007& _Other) = delete;
	AStage_007& operator=(AStage_007&& _Other) noexcept = delete;

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

