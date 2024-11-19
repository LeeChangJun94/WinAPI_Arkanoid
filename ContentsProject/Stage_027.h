#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_027 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_027();
	~AStage_027();

	// delete Function
	AStage_027(const AStage_027& _Other) = delete;
	AStage_027(AStage_027&& _Other) noexcept = delete;
	AStage_027& operator=(const AStage_027& _Other) = delete;
	AStage_027& operator=(AStage_027&& _Other) noexcept = delete;

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

