#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_019 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_019();
	~AStage_019();

	// delete Function
	AStage_019(const AStage_019& _Other) = delete;
	AStage_019(AStage_019&& _Other) noexcept = delete;
	AStage_019& operator=(const AStage_019& _Other) = delete;
	AStage_019& operator=(AStage_019&& _Other) noexcept = delete;

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

