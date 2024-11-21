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

// ���� :
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
	void TextOFF();
	void StageStart();
	void ActorSpawn();

	void StageResetSetting(int _StageCount);
	void SetCountTime(float _CountTime)
	{
		CountTime = _CountTime;
	}

	void LoadBrick(int _Stage, APlayerLife* _PlayerLifeActor);
	void ClearBrick();

	bool Timer(float _CountTime, float _SetTime, float _EndTime);
	bool Timer(float _CountTime, float _SetTime);

	static std::list<ABrick*> BrickList;
	static std::list<ABrick*> Bricks;

protected:

private:
	int Stage = 1;
	float CountTime = 0.0f;

	bool StageSetting = false;
	
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

