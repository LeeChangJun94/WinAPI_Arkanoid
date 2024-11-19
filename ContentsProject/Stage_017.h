#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_017 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_017();
	~AStage_017();

	// delete Function
	AStage_017(const AStage_017& _Other) = delete;
	AStage_017(AStage_017&& _Other) noexcept = delete;
	AStage_017& operator=(const AStage_017& _Other) = delete;
	AStage_017& operator=(AStage_017&& _Other) noexcept = delete;

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

