#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_014 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_014();
	~AStage_014();

	// delete Function
	AStage_014(const AStage_014& _Other) = delete;
	AStage_014(AStage_014&& _Other) noexcept = delete;
	AStage_014& operator=(const AStage_014& _Other) = delete;
	AStage_014& operator=(AStage_014&& _Other) noexcept = delete;

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

