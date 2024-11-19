#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_021 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_021();
	~AStage_021();

	// delete Function
	AStage_021(const AStage_021& _Other) = delete;
	AStage_021(AStage_021&& _Other) noexcept = delete;
	AStage_021& operator=(const AStage_021& _Other) = delete;
	AStage_021& operator=(AStage_021&& _Other) noexcept = delete;

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

