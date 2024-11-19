#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_013 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_013();
	~AStage_013();

	// delete Function
	AStage_013(const AStage_013& _Other) = delete;
	AStage_013(AStage_013&& _Other) noexcept = delete;
	AStage_013& operator=(const AStage_013& _Other) = delete;
	AStage_013& operator=(AStage_013&& _Other) noexcept = delete;

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

