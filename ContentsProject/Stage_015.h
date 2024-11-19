#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_015 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_015();
	~AStage_015();

	// delete Function
	AStage_015(const AStage_015& _Other) = delete;
	AStage_015(AStage_015&& _Other) noexcept = delete;
	AStage_015& operator=(const AStage_015& _Other) = delete;
	AStage_015& operator=(AStage_015&& _Other) noexcept = delete;

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

