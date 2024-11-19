#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_031 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_031();
	~AStage_031();

	// delete Function
	AStage_031(const AStage_031& _Other) = delete;
	AStage_031(AStage_031&& _Other) noexcept = delete;
	AStage_031& operator=(const AStage_031& _Other) = delete;
	AStage_031& operator=(AStage_031&& _Other) noexcept = delete;

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

