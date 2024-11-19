#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_002 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_002();
	~AStage_002();

	// delete Function
	AStage_002(const AStage_002& _Other) = delete;
	AStage_002(AStage_002&& _Other) noexcept = delete;
	AStage_002& operator=(const AStage_002& _Other) = delete;
	AStage_002& operator=(AStage_002&& _Other) noexcept = delete;

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

