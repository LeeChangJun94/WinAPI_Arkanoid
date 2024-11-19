#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_026 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_026();
	~AStage_026();

	// delete Function
	AStage_026(const AStage_026& _Other) = delete;
	AStage_026(AStage_026&& _Other) noexcept = delete;
	AStage_026& operator=(const AStage_026& _Other) = delete;
	AStage_026& operator=(AStage_026&& _Other) noexcept = delete;

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

