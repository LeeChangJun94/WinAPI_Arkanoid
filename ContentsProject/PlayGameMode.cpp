#include "PreCompile.h"
#include "PlayGameMode.h"

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


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//BGMPlayer = UEngineSound::Play("anipang_ingame_wav.wav");

	Bricks.resize(UGlobalValue::BrickY);

	for (int i = 0; i < UGlobalValue::BrickY; ++i)
	{
		Bricks[i].resize(UGlobalValue::BrickX);
	}

	Vaus = GetWorld()->GetPawn<APlayer>();
	//
	APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();
	Stage1->SetPlayMapType(EPlayMapType::TYPE_1);
	//{
	//	ANewPlayer* Actor = GetWorld()->GetPawn<ANewPlayer>();
	//	Actor->SetColImage("bg001_Col.png");
	//}
	//
	//{
	//	APlayMap* Actor = GetWorld()->SpawnActor<APlayMap>();
	//}
	//
	//{
	//	AFade* Actor = GetWorld()->SpawnActor<AFade>();
	//}

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
	
	//Vaus->SetBall(BallActor);
	
	APlayerLife* PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();
	PlayerLifeActor->SetBall(BallActor);
	PlayerLifeActor->SetDethLine(DethLineActor);
	PlayerLifeActor->BallList.push_back(BallActor);

	Vaus->SetPlayerLife(PlayerLifeActor);


	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
		return;
	}

	Dir.Append("Data");

	UEngineSerializer Ser;

	std::string FilePath = Dir.GetPathToString() + "\\Stage1.BDATA";

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
		Print->SetPlayerLife(PlayerLifeActor);
		Bricks[TilePoint.Y][TilePoint.X] = Print;
	}


	//for (int i = 0; i < 10; ++i)
	//{
	//	for (int j = 0; j < 5; ++j)
	//	{
	//		ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
	//		Ptr->SetActorLocation({ 48 + (48 * i), 160 + (24 * j) });
	//		Ptr->SetBrickType(EBrickType::WHITE);
	//		Ptr->SetPlayerLife(PlayerLifeActor);
	//		BrickPtr.push_back(Ptr);
	//	}
	//}
}

