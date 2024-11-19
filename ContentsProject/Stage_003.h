#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_003 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_003();
	~AStage_003();

	// delete Function
	AStage_003(const AStage_003& _Other) = delete;
	AStage_003(AStage_003&& _Other) noexcept = delete;
	AStage_003& operator=(const AStage_003& _Other) = delete;
	AStage_003& operator=(AStage_003&& _Other) noexcept = delete;

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

