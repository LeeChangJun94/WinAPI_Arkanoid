#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// ���� :
class AStage_022 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_022();
	~AStage_022();

	// delete Function
	AStage_022(const AStage_022& _Other) = delete;
	AStage_022(AStage_022&& _Other) noexcept = delete;
	AStage_022& operator=(const AStage_022& _Other) = delete;
	AStage_022& operator=(AStage_022&& _Other) noexcept = delete;

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

