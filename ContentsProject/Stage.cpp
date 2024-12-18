#include "PreCompile.h"
#include "Stage.h"

#include <EngineCore/Level.h>
#include <EngineBase/TimeEvent.h>
#include "GlobalValue.h"
#include "PlayMap.h"
#include "Score.h"
#include "Brick.h"
#include "Ball.h"
#include "Text.h"
#include "Fade.h"
#include "Intro.h"
#include "Number.h"
#include "Player.h"
#include "Enemies.h"
#include "DeathLine.h"
#include "PlayerLife.h"
#include "Stage_Boss.h"
#include "ContentsEnum.h"
#include "TitleGameMode.h"
#include <EngineBase/EngineFile.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

std::list<ABrick*> AStage::BrickList;
std::list<ABrick*> AStage::Bricks;
int AStage::Stage = 1;
float AStage::StageCountTime = 0.0f;
bool AStage::StageStartSound = true;

AStage::AStage()
{
}

AStage::~AStage()
{
}

void AStage::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();

	{
		AScore* Score = GetWorld()->SpawnActor<AScore>();

		Score->SetTextSpriteName("Score");
		Score->SetOrder(ERenderOrder::UI);
		Score->SetTextScale({ 24, 24 });
		Score->SetActorLocation({ 156, 36 });
		Score->SetScoreType(EScoreType::SCORE);
	}

	{
		AScore* HighScore = GetWorld()->SpawnActor<AScore>();

		HighScore->SetTextSpriteName("Score");
		HighScore->SetOrder(ERenderOrder::UI);
		HighScore->SetTextScale({ 24, 24 });
		HighScore->SetActorLocation({ 396, 36 });
		HighScore->SetScoreType(EScoreType::HIGHSCORE);
	}

	{
		Text1 = GetWorld()->SpawnActor<AText>();

		Text1->SetTextSpriteName("Text_White");
		Text1->SetOrder(ERenderOrder::UI);
		Text1->SetTextScale({ 24, 24 });
		Text1->SetActorLocation({ 260, 524 });
		Text1->SetText("ROUND", false);

		Text2 = GetWorld()->SpawnActor<AText>();

		Text2->SetTextSpriteName("Text_White");
		Text2->SetOrder(ERenderOrder::UI);
		Text2->SetTextScale({ 24, 24 });
		Text2->SetActorLocation({ 420, 524 });


		Text3 = GetWorld()->SpawnActor<AText>();

		Text3->SetTextSpriteName("Text_White");
		Text3->SetOrder(ERenderOrder::UI);
		Text3->SetTextScale({ 24, 24 });
		Text3->SetActorLocation({ 290, 572 });
		Text3->SetText("READY", false);
	}

	ADeathLine* DeathLineActor = GetWorld()->SpawnActor<ADeathLine>();

	PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetDeathLine(DeathLineActor);
	
	Vaus->SetPlayerLife(PlayerLifeActor);

	Text1->SetActive(false);
	Text2->SetActive(false);
	Text3->SetActive(false);
}

void AStage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		BGMPlayer.Stop();
		UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	UEngineDebug::CoreOutPutString("BrickListSize : " + std::to_string(BrickList.size()));
	StageCountTime += _DeltaTime;
	
	if (true == StageStartSound && 0.1 > StageCountTime)
	{
		StageStartSound = false;
		BGMPlayer = UEngineSound::Play("02 Round Start.mp3");
		BGMPlayer.SetVolume(0.2f);
	}

	Text1->SetActive(Timer(StageCountTime, 0.5f, 1.5f));
	Text2->SetActive(Timer(StageCountTime, 0.5f, 1.5f));
	Text3->SetActive(Timer(StageCountTime, 1.0f, 1.5f));



	if (true == Timer(StageCountTime, 2.0f) && true == Vaus->GetStartSwitch())
	{
		Vaus->SetStartSwitch(false);
		ActorSpawn();
	}

	if (0 == BrickList.size() && true == BrickClear)
	{
		BrickClear = false;
		TimeEventer.PushEvent(2.0f, [this]()
			{
				StageResetSetting(1);
				UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
			});
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SUBTRACT))
	{
		if (1 != Stage)
		{
			StageResetSetting(-1);
			BGMPlayer.Stop();
			UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
		}
		else
		{
			StageResetSetting(0);
			BGMPlayer.Stop();
			UEngineAPICore::GetCore()->ResetLevel<AIntro, AActor>("Intro");
			UEngineAPICore::GetCore()->OpenLevel("Intro");
		}
	}

	if (true == UEngineInput::GetInst().IsDown(VK_ADD))
	{
		if (32 != Stage)
		{
			StageResetSetting(1);
			BGMPlayer.Stop();
			UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
		}
		else
		{
			StageResetSetting(0);
			BGMPlayer.Stop();
			UEngineAPICore::GetCore()->ResetLevel<AStage_Boss, APlayer>("Stage_Boss");
			UEngineAPICore::GetCore()->OpenLevel("Stage_Boss");
		}
	}
}

void AStage::ActorSpawn()
{
	Vaus->SetActive(true);
	Vaus->GetCollisionComponent()->SetActive(true);
	BallActor = GetWorld()->SpawnActor<ABall>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->BallList.push_back(BallActor);
}


void AStage::LevelChangeStart()
{
	Super::LevelChangeStart();
	if (33 == Stage)
	{
		Stage -= 1;
	}

	Text2->SetText(Stage, false);

	Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(static_cast<EPlayMapType>(Stage % 4));
	LoadBrick(Stage, PlayerLifeActor);
	BrickClear = true;
}

void AStage::LevelChangeEnd()
{
	Super::LevelChangeEnd();
	BGMPlayer.Stop();
}

void AStage::LoadBrick(int _Stage, APlayerLife* _PlayerLifeActor)
{
	StageSetting = true;

	ClearBrick();

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Data");

	UEngineSerializer Ser;

	std::string CurStage = std::to_string(_Stage);

	std::string FilePath = Dir.GetPathToString() + "\\" + "Stage" + CurStage + ".BData";

	UEngineFile File = FilePath;
	File.FileOpen("rb");
	File.Read(Ser);

	std::vector<FVector2D> Positions;
	std::vector<int> Types;

	Ser >> Positions;
	Ser >> Types;

	for (size_t i = 0; i < Positions.size(); i++)
	{
		FVector2D IndexPos = (Positions[i] - UGlobalValue::StartBrickPos) / UGlobalValue::BrickSize;
		FIntPoint TilePoint = IndexPos.ConvertToPoint();

		FVector2D CreatePos;
		CreatePos.X = TilePoint.X * UGlobalValue::BrickSize.X;
		CreatePos.Y = TilePoint.Y * UGlobalValue::BrickSize.Y;
		CreatePos += UGlobalValue::StartBrickPos;

		ABrick* Print = GetWorld()->SpawnActor<ABrick>();
		Print->SetActorLocation(CreatePos + UGlobalValue::BrickSize.Half());
		Print->SetBrickType(static_cast<EBrickType>(Types[i]));
		Print->SetPlayerLife(_PlayerLifeActor);
		Bricks.push_back(Print);
		if (Types[i] < 9)
		{
			BrickList.push_back(Print);
		}
	}
}

void AStage::ClearBrick()
{
	
	std::list<ABrick*>::iterator BricksStart = Bricks.begin();
	std::list<ABrick*>::iterator BricksEnd = Bricks.end();
	
	for (; BricksStart != BricksEnd; )
	{
		if (nullptr != (*BricksStart))
		{
			(*BricksStart)->Destroy();
			(*BricksStart) = nullptr;
			BricksStart = Bricks.erase(BricksStart);
		}
	}
}

bool AStage::Timer(float _CountTime, float _SetTime, float _EndTime)
{
	if (_SetTime < _CountTime && _EndTime > _CountTime)
	{
		return true;
	}
	return false;
}

bool AStage::Timer(float _CountTime, float _SetTime)
{
	if (_SetTime < _CountTime)
	{
		return true;
	}
	return false;
}

void AStage::StageResetSetting(int _StageCount)
{
	Stage += _StageCount;
	StageStartSound = true;
	StageSetting = false;
	Vaus->SetStartSwitch(true);
	Vaus->SetActive(false);
	Vaus->ChangeState(PlayerState::Create);
	StageCountTime = 0.0f;
	BrickList.clear();
	Map->Destroy();
	Text2->SetText(Stage, false);
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