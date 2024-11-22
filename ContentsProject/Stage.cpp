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
#include "Number.h"
#include "Player.h"
#include "Enemies.h"
#include "DethLine.h"
#include "PlayerLife.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineFile.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

std::list<ABrick*> AStage::BrickList;
std::list<ABrick*> AStage::Bricks;


AStage::AStage()
{
	//Bricks.resize(UGlobalValue::BrickY);
	//
	//for (int i = 0; i < UGlobalValue::BrickY; ++i)
	//{
	//	Bricks[i].resize(UGlobalValue::BrickX);
	//}
}

AStage::~AStage()
{
}

void AStage::BeginPlay()
{
	Super::BeginPlay();
	
	//BGMPlayer = UEngineSound::Play("anipang_ingame_wav.wav");
	
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
		Text1 = GetWorld()->SpawnActor<AText>();

		Text1->SetTextSpriteName("Text");
		Text1->SetOrder(ERenderOrder::UI);
		Text1->SetTextScale({ 24, 24 });
		Text1->SetActorLocation({ 350, 524 });
		Text1->SetText("ROUND");

		Text2 = GetWorld()->SpawnActor<ANumber>();

		Text2->SetNumberSpriteName("Number");
		Text2->SetOrder(ERenderOrder::UI);
		Text2->SetNumberScale({ 24, 24 });
		Text2->SetActorLocation({ 419, 524 });
		Text2->SetNumber(Stage);

		Text3 = GetWorld()->SpawnActor<AText>();

		Text3->SetTextSpriteName("Text");
		Text3->SetOrder(ERenderOrder::UI);
		Text3->SetTextScale({ 24, 24 });
		Text3->SetActorLocation({ 380, 572 });
		Text3->SetText("READY");
	}
	//AEnemies* Enemies = GetWorld()->SpawnActor<AEnemies>();
	//Enemies->SetActorLocation({ 50,50 });

	ADethLine* DethLineActor = GetWorld()->SpawnActor<ADethLine>();

	PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetDethLine(DethLineActor);
	
	Vaus->SetPlayerLife(PlayerLifeActor);

	Text1->SetActive(false);
	Text2->SetActive(false);
	Text3->SetActive(false);
	//Vaus->SetActive(false);
	//BallActor->SetActive(false);

	//LoadBrick(Stage, PlayerLifeActor);
}

void AStage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	UEngineDebug::CoreOutPutString("BrickListSize : " + std::to_string(BrickList.size()));
	CountTime += _DeltaTime;

	Text1->SetActive(Timer(CountTime, 0.5f, 1.5f));
	Text2->SetActive(Timer(CountTime, 0.5f, 1.5f));
	Text3->SetActive(Timer(CountTime, 1.0f, 1.5f));

	if (true != StageSetting)
	{
		Map = GetWorld()->SpawnActor<APlayMap>();
		Map->SetPlayMapType(static_cast<EPlayMapType>(Stage % 4));
		LoadBrick(Stage, PlayerLifeActor);
	}

	if (true == Timer(CountTime, 2.0f) && true == Vaus->GetStartSwitch())
	{
		Vaus->SetStartSwitch(false);
		ActorSpawn();
	}

	if (0 == BrickList.size())
	{
		StageResetSetting(1);
		TimeEventer.PushEvent(1.0f, []()
			{
				UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
			});
	}

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

void AStage::TextOFF()
{
	Text1->SetActive(false);
	Text2->SetActive(false);
	Text3->SetActive(false);
}

void AStage::StageStart()
{
	//TimeEventer.PushEvent(0.5f, [this]()
	//	{
	//		Text1->SetActive(true);
	//	}
	//, false, false);
	//
	//TimeEventer.PushEvent(0.5f, [this]()
	//	{
	//		Text2->SetActive(true);
	//	}
	//, false, false);
	//
	//TimeEventer.PushEvent(1.0f, [this]()
	//	{
	//		Text3->SetActive(true);
	//	}
	//, false, false);

	//TimeEventer.PushEvent(1.5f, std::bind(&AStage_001::TextOFF, this), false, false);

	//TimeEventer.PushEvent(2.0f, std::bind(&AStage_001::ActorSpawn, this), false, false);
}

void AStage::ActorSpawn()
{
	Vaus->SetActive(true);
	Vaus->GetCollisionComponent()->SetActive(true);
	BallActor = GetWorld()->SpawnActor<ABall>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->BallList.push_back(BallActor);
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

	//for (size_t y = 0; y < Bricks.size(); y++)
	//{
	//	for (size_t x = 0; x < Bricks[y].size(); x++)
	//	{
	//		if (nullptr != Bricks[y][x])
	//		{
	//			Bricks[y][x]->Destroy();
	//			Bricks[y][x] = nullptr;
	//		}
	//	}
	//}
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
	StageSetting = false;
	Vaus->SetStartSwitch(true);
	Vaus->SetActive(false);
	Vaus->ChangeState(PlayerState::Create);
	CountTime = 0.0f;
	BrickList.clear();
	Map->Destroy();
	Text2->SetNumber(Stage);
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