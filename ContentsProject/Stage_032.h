#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_032 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_032();
	~AStage_032();

	// delete Function
	AStage_032(const AStage_032& _Other) = delete;
	AStage_032(AStage_032&& _Other) noexcept = delete;
	AStage_032& operator=(const AStage_032& _Other) = delete;
	AStage_032& operator=(AStage_032&& _Other) noexcept = delete;

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

