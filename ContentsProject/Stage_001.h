#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_001 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_001();
	~AStage_001();

	// delete Function
	AStage_001(const AStage_001& _Other) = delete;
	AStage_001(AStage_001&& _Other) noexcept = delete;
	AStage_001& operator=(const AStage_001& _Other) = delete;
	AStage_001& operator=(AStage_001&& _Other) noexcept = delete;

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

