#include "PreCompile.h"
#include "Stage_Boss.h"

#include <EngineCore/Level.h>
#include <EngineBase/TimeEvent.h>
#include "GlobalValue.h"
#include "PlayMap.h"
#include "Score.h"
#include "Brick.h"
#include "Boss.h"
#include "Ball.h"
#include "Text.h"
#include "Number.h"
#include "Player.h"
#include "Enemies.h"
#include "DethLine.h"
#include "PlayerLife.h"
#include "BossBullet.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineFile.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

AStage_Boss::AStage_Boss()
{
	//Boss_Brick 144 280
	//Boss 	243 120
}

AStage_Boss::~AStage_Boss()
{
}

void AStage_Boss::BeginPlay()
{
	Super::BeginPlay();

	//BGMPlayer = UEngineSound::Play("anipang_ingame_wav.wav");

	Boss = GetWorld()->SpawnActor<ABoss>();
	Boss->SetActorLocation({ 336, 312 });

	
	//BossBullet->SetBossBulletDir()


	Vaus = GetWorld()->GetPawn<APlayer>();

	//APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();
	//Stage1->SetPlayMapType(static_cast<EPlayMapType>(Stage % 4));

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

	{
		//Text1 = GetWorld()->SpawnActor<AText>();
		//
		//Text1->SetTextSpriteName("Text");
		//Text1->SetOrder(ERenderOrder::UI);
		//Text1->SetTextScale({ 24, 24 });
		//Text1->SetActorLocation({ 350, 524 });
		//Text1->SetText("ROUND");
		//
		//Text2 = GetWorld()->SpawnActor<ANumber>();
		//
		//Text2->SetNumberSpriteName("Number");
		//Text2->SetOrder(ERenderOrder::UI);
		//Text2->SetNumberScale({ 24, 24 });
		//Text2->SetActorLocation({ 419, 524 });
		//Text2->SetNumber(Stage);
		//
		//Text3 = GetWorld()->SpawnActor<AText>();
		//
		//Text3->SetTextSpriteName("Text");
		//Text3->SetOrder(ERenderOrder::UI);
		//Text3->SetTextScale({ 24, 24 });
		//Text3->SetActorLocation({ 380, 572 });
		//Text3->SetText("READY");
	}
	//AEnemies* Enemies = GetWorld()->SpawnActor<AEnemies>();
	//Enemies->SetActorLocation({ 50,50 });

	ADethLine* DethLineActor = GetWorld()->SpawnActor<ADethLine>();

	PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetDethLine(DethLineActor);

	Vaus->SetPlayerLife(PlayerLifeActor);

	//Text1->SetActive(false);
	//Text2->SetActive(false);
	//Text3->SetActive(false);
	//Vaus->SetActive(false);
	//BallActor->SetActive(false);

	//LoadBrick(Stage, PlayerLifeActor);
}

void AStage_Boss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("BossHP : " + std::to_string(BossHP));
	CountTime += _DeltaTime;

	
	
	//if (3 == (static_cast<int>(CountTime) % 4) && true != BossAttack)
	//{
	//	BossAttack = true;

	//	TimeEventer.PushEvent(0.0f, [this]()
	//		{
	//			ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
	//			BossBullet->SetActorLocation({ 336, 312 });
	//		});
	//	TimeEventer.PushEvent(0.5f, [this]()
	//		{
	//			ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
	//			BossBullet->SetActorLocation({ 336, 312 });
	//		});
	//	TimeEventer.PushEvent(1.0f, [this]()
	//		{
	//			ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
	//			BossBullet->SetActorLocation({ 336, 312 });
	//		});
	//	TimeEventer.PushEvent(1.5f, [this]()
	//		{
	//			ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
	//			BossBullet->SetActorLocation({ 336, 312 });
	//		});
	//	TimeEventer.PushEvent(2.0f, [this]()
	//		{
	//			ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
	//			BossBullet->SetActorLocation({ 336, 312 });
	//			BossAttack = false;
	//		});
	//}
	
	if (true != StageSetting)
	{
		Map = GetWorld()->SpawnActor<APlayMap>();
		Map->SetPlayMapType(EPlayMapType::TYPE_BOSS);
		TimeEventer.PushEvent(2.0f, [this]()
			{
				Boss->GetSpriteRenderer()->ChangeAnimation("Boss_Normal");
			});
		StageSetting = true;
	}

	if (true == Timer(CountTime, 2.0f) && true == Vaus->GetStartSwitch())
	{
		Vaus->SetStartSwitch(false);
		ActorSpawn();
	}

	//if (0 == BrickList.size())
	//{
	//	StageResetSetting(1);
	//	TimeEventer.PushEvent(1.0f, []()
	//		{
	//			UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
	//		});
	//}

	if (true == UEngineInput::GetInst().IsDown('N'))
	{
		if (1 != Stage)
		{
			StageResetSetting(-1);

			UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
		}
		else
		{
			StageResetSetting(0);

			UEngineAPICore::GetCore()->OpenLevel("Title");
		}
	}

	if (true == UEngineInput::GetInst().IsDown('M'))
	{
		if (32 != Stage)
		{
			StageResetSetting(1);

			UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
		}
		else
		{
			StageResetSetting(0);

			UEngineAPICore::GetCore()->OpenLevel("Stage_Boss");
		}
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
	Stage += _StageCount;
	StageSetting = false;
	Vaus->SetStartSwitch(true);
	Vaus->SetActive(false);
	Vaus->ChangeState(PlayerState::Create);
	CountTime = 0.0f;
	//BrickList.clear();
	Map->Destroy();
	//Text2->SetNumber(Stage);
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
	Vaus->SetStartSwitch(true);
	Vaus->ChangeState(PlayerState::Destroy);
	CountTime = 0.0f;
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