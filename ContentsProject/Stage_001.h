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
class APlayMap;

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

	void StageResetSetting(int _StageCount);

	void LoadBrick(int _Stage, APlayerLife* _PlayerLifeActor);
	void ClearBrick();

	bool Timer(float _CountTime, float _SetTime, float _EndTime);
	bool Timer(float _CountTime, float _SetTime);

	static std::list<ABrick*> BrickList;

	

protected:

private:
	int Stage = 1;
	float CountTime = 0.0f;

	bool StageSetting = false;
	
	//int BrickCount = 0;
	
	APlayMap* Map = nullptr;
	APlayer* Vaus = nullptr;
	ABall* BallActor = nullptr;
	AText* Text1 = nullptr;
	ANumber* Text2 = nullptr;
	AText* Text3 = nullptr;
	APlayerLife* PlayerLifeActor = nullptr;
	std::vector<std::vector<ABrick*>> Bricks;
	USoundPlayer BGMPlayer;

};

