#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;

// Ό³Έν :
class AStage_009 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_009();
	~AStage_009();

	// delete Function
	AStage_009(const AStage_009& _Other) = delete;
	AStage_009(AStage_009&& _Other) noexcept = delete;
	AStage_009& operator=(const AStage_009& _Other) = delete;
	AStage_009& operator=(AStage_009&& _Other) noexcept = delete;

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

