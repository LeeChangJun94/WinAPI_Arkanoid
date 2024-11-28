#include "PreCompile.h"
#include "Stage_Boss.h"

#include <EngineCore/Level.h>
#include <EngineBase/TimeEvent.h>
#include "GlobalValue.h"
#include "PlayMap.h"
#include "Stage.h"
#include "Score.h"
#include "Brick.h"
#include "Boss.h"
#include "Ball.h"
#include "Text.h"
#include "Number.h"
#include "Player.h"
#include "Outtro.h"
#include "Enemies.h"
#include "DeathLine.h"
#include "PlayerLife.h"
#include "BossBullet.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineFile.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

float AStage_Boss::BossCountTime = 0.0f;
bool AStage_Boss::BossStartSound = true;

AStage_Boss::AStage_Boss()
{
}

AStage_Boss::~AStage_Boss()
{
}

void AStage_Boss::BeginPlay()
{
	Super::BeginPlay();
	AStage::Stage = 33;
	Boss = GetWorld()->SpawnActor<ABoss>();
	Boss->SetActorLocation({ 336, 312 });

	Vaus = GetWorld()->GetPawn<APlayer>();

	{
		AScore* Score = GetWorld()->SpawnActor<AScore>();

		Score->SetTextSpriteName("Score");
		Score->SetOrder(ERenderOrder::UI);
		Score->SetTextScale({ 24, 24 });
		Score->SetActorLocation({ 156, 36 });
	}

	{
		AScore* HighScore = GetWorld()->SpawnActor<AScore>();

		HighScore->SetTextSpriteName("Score");
		HighScore->SetOrder(ERenderOrder::UI);
		HighScore->SetTextScale({ 24, 24 });
		HighScore->SetActorLocation({ 396, 36 });
	}

	ADeathLine* DeathLineActor = GetWorld()->SpawnActor<ADeathLine>();

	PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetDeathLine(DeathLineActor);
	PlayerLifeActor->SetBoss(Boss);

	Vaus->SetPlayerLife(PlayerLifeActor);
}

void AStage_Boss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
		
	BossCountTime += _DeltaTime;
	
	if (true == BossStartSound && 0.1f > BossCountTime)
	{
		BossStartSound = false;
		BGMPlayer = UEngineSound::Play("03 Doh Round.mp3");
		BGMPlayer.SetVolume(0.2f);
	}

	if (true != StageSetting)
	{
		Map = GetWorld()->SpawnActor<APlayMap>();
		Map->SetPlayMapType(EPlayMapType::TYPE_BOSS);
		StageSetting = true;
	}

	if (/*true == Timer(BossCountTime, 2.0f)*/2.0f < BossCountTime && true == Vaus->GetStartSwitch())
	{
		Vaus->SetStartSwitch(false);
		ActorSpawn();
	}

	if (BossState::DESTROY == Boss->GetCurBossState())
	{
		std::list<ABall*>::iterator BalliterStart = PlayerLifeActor->BallList.begin();
		std::list<ABall*>::iterator BalliterEnd = PlayerLifeActor->BallList.end();
		for (; BalliterStart != BalliterEnd; )
		{
			(*BalliterStart)->Destroy();
			(*BalliterStart) = nullptr;
			BalliterStart = PlayerLifeActor->BallList.erase(BalliterStart);
		}
		
		TimeEventer.PushEvent(3.5f, [this]()
			{
				UEngineAPICore::GetCore()->OpenLevel("Outtro");
			});
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SUBTRACT))
	{
		StageResetSetting(0);

		UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_ADD))
	{
		StageResetSetting(0);
		UEngineAPICore::GetCore()->ResetLevel<AOuttro, AActor>("Outtro");
		UEngineAPICore::GetCore()->OpenLevel("Outtro");
	}
}

void AStage_Boss::ActorSpawn()
{
	Vaus->SetActive(true);
	Vaus->GetCollisionComponent()->SetActive(true);
	BallActor = GetWorld()->SpawnActor<ABall>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->BallList.push_back(BallActor);
}

bool AStage_Boss::Timer(float _CountTime, float _SetTime, float _EndTime)
{
	if (_SetTime < _CountTime && _EndTime > _CountTime)
	{
		return true;
	}
	return false;
}

bool AStage_Boss::Timer(float _CountTime, float _SetTime)
{
	if (_SetTime < _CountTime)
	{
		return true;
	}
	return false;
}

void AStage_Boss::StageResetSetting(int _StageCount)
{
	AStage::Stage += _StageCount;
	AStage::StageStartSound = true;
	StageSetting = false;
	Vaus->SetStartSwitch(true);
	Vaus->SetActive(false);
	Vaus->ChangeState(PlayerState::Create);
	BossCountTime = 0.0f;
	Map->Destroy();
	Vaus->BulletPtr.clear();
	std::list<ABall*>::iterator BalliterStart = PlayerLifeActor->BallList.begin();
	std::list<ABall*>::iterator BalliterEnd = PlayerLifeActor->BallList.end();
	for (; BalliterStart != BalliterEnd; )
	{
		(*BalliterStart)->Destroy();
		(*BalliterStart) = nullptr;
		BalliterStart = PlayerLifeActor->BallList.erase(BalliterStart);
	}
}

void AStage_Boss::StageResetSetting()
{
	StageSetting = false;
	BossStartSound = true;
	Vaus->SetStartSwitch(true);
	Vaus->ChangeState(PlayerState::Destroy);
	Boss->GetSpriteRenderer()->SetSprite("Boss.png", 0);
	Boss->SetCountTime(-1.0f);
	//BossCountTime = 0.0f;
	Map->Destroy();
	std::list<ABall*>::iterator BalliterStart = PlayerLifeActor->BallList.begin();
	std::list<ABall*>::iterator BalliterEnd = PlayerLifeActor->BallList.end();
	for (; BalliterStart != BalliterEnd; )
	{
		(*BalliterStart)->Destroy();
		(*BalliterStart) = nullptr;
		BalliterStart = PlayerLifeActor->BallList.erase(BalliterStart);
	}
}