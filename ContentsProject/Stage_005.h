#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_005 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_005();
	~AStage_005();

	// delete Function
	AStage_005(const AStage_005& _Other) = delete;
	AStage_005(AStage_005&& _Other) noexcept = delete;
	AStage_005& operator=(const AStage_005& _Other) = delete;
	AStage_005& operator=(AStage_005&& _Other) noexcept = delete;

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

