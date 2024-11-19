#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_012 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_012();
	~AStage_012();

	// delete Function
	AStage_012(const AStage_012& _Other) = delete;
	AStage_012(AStage_012&& _Other) noexcept = delete;
	AStage_012& operator=(const AStage_012& _Other) = delete;
	AStage_012& operator=(AStage_012&& _Other) noexcept = delete;

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

