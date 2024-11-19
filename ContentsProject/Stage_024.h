#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_024 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_024();
	~AStage_024();

	// delete Function
	AStage_024(const AStage_024& _Other) = delete;
	AStage_024(AStage_024&& _Other) noexcept = delete;
	AStage_024& operator=(const AStage_024& _Other) = delete;
	AStage_024& operator=(AStage_024&& _Other) noexcept = delete;

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

