#include "PreCompile.h"
#include "Stage_026.h"

#include <EngineCore/Level.h>
#include "GlobalValue.h"
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Player.h"
#include "PlayerLife.h"
#include "Fade.h"
#include "DethLine.h"
#include "ContentsEnum.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

AStage_026::AStage_026()
{
}

AStage_026::~AStage_026()
{
}

void AStage_026::BeginPlay()
{
	Super::BeginPlay();

	//BGMPlayer = UEngineSound::Play("anipang_ingame_wav.wav");

	Vaus = GetWorld()->GetPawn<APlayer>();

	APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();
	Stage1->SetPlayMapType(EPlayMapType::TYPE_2);

	{
		AScore* Score = GetWorld()->SpawnActor<AScore>();

		Score->SetTextSpriteName("Text");
		Score->SetOrder(ERenderOrder::UI);
		Score->SetTextScale({ 24, 24 });
		Score->SetActorLocation({ 156, 36 });
	}

	{
		AScore* HighScore = GetWorld()->SpawnActor<AScore>();

		HighScore->SetTextSpriteName("Text");
		HighScore->SetOrder(ERenderOrder::UI);
		HighScore->SetTextScale({ 24, 24 });
		HighScore->SetActorLocation({ 396, 36 });
	}

	ADethLine* DethLineActor = GetWorld()->SpawnActor<ADethLine>();

	ABall* BallActor = GetWorld()->SpawnActor<ABall>();

	APlayerLife* PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->SetDethLine(DethLineActor);
	PlayerLifeActor->BallList.push_back(BallActor);

	Vaus->SetPlayerLife(PlayerLifeActor);

	LoadBrick("Stage26", PlayerLifeActor);
}

void AStage_026::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('N'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage_025");
	}

	if (true == UEngineInput::GetInst().IsDown('M'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage_027");
	}
}

void AStage_026::LoadBrick(std::string _Stage, APlayerLife* _PlayerLifeActor)
{
	Bricks.resize(UGlobalValue::BrickY);

	for (int i = 0; i < UGlobalValue::BrickY; ++i)
	{
		Bricks[i].resize(UGlobalValue::BrickX);
	}

	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Data");

	UEngineSerializer Ser;

	std::string FilePath = Dir.GetPathToString() + "\\" + _Stage + ".BData";

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
	}
}