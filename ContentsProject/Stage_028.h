#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_028 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_028();
	~AStage_028();

	// delete Function
	AStage_028(const AStage_028& _Other) = delete;
	AStage_028(AStage_028&& _Other) noexcept = delete;
	AStage_028& operator=(const AStage_028& _Other) = delete;
	AStage_028& operator=(AStage_028&& _Other) noexcept = delete;

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

