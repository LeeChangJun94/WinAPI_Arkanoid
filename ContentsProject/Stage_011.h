#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_011 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_011();
	~AStage_011();

	// delete Function
	AStage_011(const AStage_011& _Other) = delete;
	AStage_011(AStage_011&& _Other) noexcept = delete;
	AStage_011& operator=(const AStage_011& _Other) = delete;
	AStage_011& operator=(AStage_011&& _Other) noexcept = delete;

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

