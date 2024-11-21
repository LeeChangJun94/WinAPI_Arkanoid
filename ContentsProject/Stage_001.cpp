#include "PreCompile.h"
#include "Stage_001.h"

#include <EngineCore/Level.h>
#include <EngineBase/TimeEvent.h>
#include "GlobalValue.h"
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Text.h"
#include "Number.h"
#include "Player.h"
#include "PlayerLife.h"
#include "Fade.h"
#include "DethLine.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

std::list<ABrick*> AStage_001::BrickList;

AStage_001::AStage_001()
{
	Bricks.resize(UGlobalValue::BrickY);

	for (int i = 0; i < UGlobalValue::BrickY; ++i)
	{
		Bricks[i].resize(UGlobalValue::BrickX);
	}
}

AStage_001::~AStage_001()
{
}

void AStage_001::BeginPlay()
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

void AStage_001::Tick(float _DeltaTime)
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
		//Stage += 1;
		//StageSetting = false;
		//Vaus->SetStartSwitch(true);
		//Vaus->SetActive(false);
		//Vaus->ChangeState(PlayerState::Create);
		//CountTime = 0.0f;
		//BrickList.clear();
		//Map->Destroy();
		//Text2->SetNumber(Stage);
		//if (nullptr != BallActor)
		//{
		//	BallActor->Destroy();
		//}
		UEngineAPICore::GetCore()->OpenLevel("Stage_002");
		//LoadBrick(Stage, PlayerLifeActor);
	}

	if (true == UEngineInput::GetInst().IsDown('N'))
	{
		if (1 != Stage)
		{
			StageResetSetting(-1);
			//Stage -= 1;
			//StageSetting = false;
			//Vaus->SetStartSwitch(true);
			//Vaus->SetActive(false);
			//Vaus->ChangeState(PlayerState::Create);
			//CountTime = 0.0f;
			//BrickList.clear();
			//Map->Destroy();
			//Text2->SetNumber(Stage);
			//std::list<ABall*>::iterator BalliterStart = PlayerLifeActor->BallList.begin();
			//std::list<ABall*>::iterator BalliterEnd = PlayerLifeActor->BallList.end();
			//for (; BalliterStart != BalliterEnd; ++BalliterStart)
			//{
			//	(*BalliterStart)->Destroy();
			//	(*BalliterStart) = nullptr;
			//}
			//if (nullptr != BallActor)
			//{
			//	BallActor->Destroy();
			//}
			UEngineAPICore::GetCore()->OpenLevel("Stage_002");
		}
		else
		{
			UEngineAPICore::GetCore()->OpenLevel("Title");
		}
	}

	if (true == UEngineInput::GetInst().IsDown('M'))
	{
		if (32 != Stage)
		{
			StageResetSetting(1);
			//Stage += 1;
			//StageSetting = false;
			//CountTime = 0.0f;
			//Vaus->SetStartSwitch(true);
			//Vaus->SetActive(false);
			//Vaus->ChangeState(PlayerState::Create);
			//BrickList.clear();
			//Map->Destroy();
			//Text2->SetNumber(Stage);
			//if (nullptr != BallActor)
			//{
			//	BallActor->Destroy();
			//}
			UEngineAPICore::GetCore()->OpenLevel("Stage_002");
		}
		else
		{
			UEngineAPICore::GetCore()->OpenLevel("Stage_Boss");
		}
	}
}

void AStage_001::TextOFF()
{
	Text1->SetActive(false);
	Text2->SetActive(false);
	Text3->SetActive(false);
}

void AStage_001::StageStart()
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

void AStage_001::ActorSpawn()
{
	Vaus->SetActive(true);
	BallActor = GetWorld()->SpawnActor<ABall>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->BallList.push_back(BallActor);
}

void AStage_001::LoadBrick(int _Stage, APlayerLife* _PlayerLifeActor)
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
		Bricks[TilePoint.Y][TilePoint.X] = Print;
		if (Types[i] < 8)
		{
			BrickList.push_back(Print);
		}
	}
}

void AStage_001::ClearBrick()
{
	for (size_t y = 0; y < Bricks.size(); y++)
	{
		for (size_t x = 0; x < Bricks[y].size(); x++)
		{
			if (nullptr != Bricks[y][x])
			{
				Bricks[y][x]->Destroy();
				Bricks[y][x] = nullptr;
			}
		}
	}
}

bool AStage_001::Timer(float _CountTime, float _SetTime, float _EndTime)
{
	if (_SetTime < _CountTime && _EndTime > _CountTime)
	{
		return true;
	}
	return false;
}

bool AStage_001::Timer(float _CountTime, float _SetTime)
{
	if (_SetTime < _CountTime)
	{
		return true;
	}
	return false;
}

void AStage_001::StageResetSetting(int _StageCount)
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
	std::list<ABall*>::iterator BalliterStart = PlayerLifeActor->BallList.begin();
	std::list<ABall*>::iterator BalliterEnd = PlayerLifeActor->BallList.end();
	for (; BalliterStart != BalliterEnd; )
	{
		(*BalliterStart)->Destroy();
		(*BalliterStart) = nullptr;
		BalliterStart = PlayerLifeActor->BallList.erase(BalliterStart);
	}
}