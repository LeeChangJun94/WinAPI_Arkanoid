#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
#include <vector>

#include "Brick.h"

class APlayer;
class ABall;
class AText;
class ANumber;
class AScore;
class APlayerLife;

// Ό³Έν :
class AStage_001 : public AGameMode
{
public:
	// constrcuter destructer
	AStage_001();
	~AStage_001();

	// delete Function
	AStage_001(const AStage_001& _Other) = delete;
	AStage_001(AStage_001&& _Other) noexcept = delete;
	AStage_001& operator=(const AStage_001& _Other) = delete;
	AStage_001& operator=(AStage_001&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);
	void TextOFF();
	void StageStart();
	void ActorSpawn();

	void LoadBrick(std::string _Stage, APlayerLife* _PlayerLifeActor);

	std::list<ABrick*> BrickPtr;

	

protected:

private:
	int Stage = 1;
	
	APlayer* Vaus = nullptr;
	ABall* BallActor = nullptr;
	AText* Text1 = nullptr;
	ANumber* Text2 = nullptr;
	AText* Text3 = nullptr;
	APlayerLife* PlayerLifeActor = nullptr;
	std::vector<std::vector<ABrick*>> Bricks;
	USoundPlayer BGMPlayer;

};

