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
class AStage_Boss : public AGameMode
{
public:
	// constrcuter destructer
	AStage_Boss();
	~AStage_Boss();

	// delete Function
	AStage_Boss(const AStage_Boss& _Other) = delete;
	AStage_Boss(AStage_Boss&& _Other) noexcept = delete;
	AStage_Boss& operator=(const AStage_Boss& _Other) = delete;
	AStage_Boss& operator=(AStage_Boss&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	
	void ActorSpawn();

	void StageResetSetting(int _StageCount);
	void StageResetSetting();
	void SetCountTime(float _CountTime)
	{
		CountTime = _CountTime;
	}



	bool Timer(float _CountTime, float _SetTime, float _EndTime);
	bool Timer(float _CountTime, float _SetTime);



protected:

private:
	int Stage = 1;
	float CountTime = 0.0f;
	int BossHP = 10;

	bool StageSetting = false;
	bool BossAttack = false;

	APlayMap* Map = nullptr;
	APlayer* Vaus = nullptr;
	ABall* BallActor = nullptr;
	AText* Text1 = nullptr;
	ANumber* Text2 = nullptr;
	AText* Text3 = nullptr;
	APlayerLife* PlayerLifeActor = nullptr;
	//std::vector<std::vector<ABrick*>> Bricks;
	USoundPlayer BGMPlayer;

};

