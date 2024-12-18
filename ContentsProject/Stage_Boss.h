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
class ABoss;
class APlayerLife;
class APlayMap;

// ���� :
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


	bool Timer(float _CountTime, float _SetTime, float _EndTime);
	bool Timer(float _CountTime, float _SetTime);

	static bool BossStartSound;
	static float BossCountTime;


protected:

private:
	//int Stage = 33;
	
	bool StageSetting = false;
	bool BossAttack = false;

	APlayMap* Map = nullptr;
	APlayer* Vaus = nullptr;
	ABall* BallActor = nullptr;
	ABoss* Boss = nullptr;
	APlayerLife* PlayerLifeActor = nullptr;
	//std::vector<std::vector<ABrick*>> Bricks;
	USoundPlayer BGMPlayer;

};

