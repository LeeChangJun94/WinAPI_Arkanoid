#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_029 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_029();
	~AStage_029();

	// delete Function
	AStage_029(const AStage_029& _Other) = delete;
	AStage_029(AStage_029&& _Other) noexcept = delete;
	AStage_029& operator=(const AStage_029& _Other) = delete;
	AStage_029& operator=(AStage_029&& _Other) noexcept = delete;

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

