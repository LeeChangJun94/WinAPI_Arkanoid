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
class AStage : public AGameMode
{
public:
	// constrcuter destructer
	AStage();
	~AStage();

	// delete Function
	AStage(const AStage& _Other) = delete;
	AStage(AStage&& _Other) noexcept = delete;
	AStage& operator=(const AStage& _Other) = delete;
	AStage& operator=(AStage&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);
	void ActorSpawn();

	void StageResetSetting(int _StageCount);
	void SetCountTime(float _CountTime)
	{
		StageCountTime = _CountTime;
	}

	void LoadBrick(int _Stage, APlayerLife* _PlayerLifeActor);
	void ClearBrick();

	bool Timer(float _CountTime, float _SetTime, float _EndTime);
	bool Timer(float _CountTime, float _SetTime);

	static std::list<ABrick*> BrickList;
	static std::list<ABrick*> Bricks;
	static int Stage;
	static float StageCountTime;
	static bool StageStartSound;

protected:

private:
	bool StageSetting = false;
	bool BrickClear = true;
	
	APlayMap* Map = nullptr;
	APlayer* Vaus = nullptr;
	ABall* BallActor = nullptr;
	AText* Text1 = nullptr;
	AText* Text2 = nullptr;
	AText* Text3 = nullptr;
	APlayerLife* PlayerLifeActor = nullptr;
	
	USoundPlayer BGMPlayer;

};

