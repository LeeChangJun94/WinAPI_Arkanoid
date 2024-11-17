#include "PreCompile.h"
#include "TileMapGameMode.h"
#include "Brick.h"
#include "PlayMap.h"
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>


ATileMapGameMode::ATileMapGameMode()
{
	//SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("Bricks.png");
	//SpriteRenderer->SetComponentScale({ 64, 32 });

}

ATileMapGameMode::~ATileMapGameMode()
{
}

// Ÿ����� ������ �� �ִ� ����
void ATileMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();
	//{
	//	GroundTileMap = GetWorld()->SpawnActor<ATileMap>();
	//	//GroundTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });
	//
	//	//for (int y = 0; y < 20; y++)
	//	//{
	//	//	for (int x = 0; x < 20; x++)
	//	//	{
	//	//		GroundTileMap->SetTileIndex({ y,x }, 0);
	//	//	}
	//	//}
	//}
	//
	//{
	//	WallTileMap = GetWorld()->SpawnActor<ATileMap>();
	//	WallTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });
	//
	//	for (int y = 0; y < 20; y++)
	//	{
	//		for (int x = 0; x < 20; x++)
	//		{
	//			WallTileMap->SetTileIndex({ y,x }, { 0, -6 }, { 32, 44 }, 2);
	//		}
	//	}
	//}

	//BrickTile = GetWorld()->SpawnActor<ATileMap>();
	//for (int i = 0; i < 10; ++i)
	//{
	//	for (int j = 0; j < 5; ++j)
	//	{
	//
	//		BrickTile->SetTileIndex({ 64 + (64 * i), 160 + (32 * j) } , 1);
	//	}
	//}

}

void ATileMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	//{
	//	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	//	WallTileMap->SetTileLocation(MousePos, 1);
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	//{
	//	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	//	Tile* Tile = WallTileMap->GetTileRef(MousePos);
	//	if (nullptr != Tile->SpriteRenderer)
	//	{
	//		Tile->SpriteRenderer->Destroy(5.0f);
	//		Tile->SpriteRenderer = nullptr;
	//	}
	//}
	//
	//
	//if (true == UEngineInput::GetInst().IsPress('R'))
	//{
	//	UEngineSerializer _Ser;
	//	WallTileMap->Serialize(_Ser);
	//	// ������ ����Ʈ ��� �׳� �����ϸ� ������.
	//	UEngineDirectory Dir;
	//
	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
	//		return;
	//	}
	//
	//	Dir.Append("Data");
	//
	//	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("wb");
	//	NewFile.Write(_Ser);
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress('P'))
	//{
	//	UEngineRandom Random;
	//	for (size_t i = 0; i < 10; i++)
	//	{
	//		int Value = Random.RandomInt(0, 100);
	//		UEngineDebug::OutPutString(std::to_string(Value));
	//	}
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress('T'))
	//{
	//	UEngineDirectory Dir;
	//
	//	if (false == Dir.MoveParentToDirectory("Resources"))
	//	{
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
	//		return;
	//	}
	//
	//	Dir.Append("Data");
	//
	//	std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
	//	UEngineFile NewFile = SaveFilePath;
	//	NewFile.FileOpen("rb");
	//
	//	UEngineSerializer Ser;
	//	NewFile.Read(Ser);
	//
	//
	//	WallTileMap->DeSerialize(Ser);
	//
	//}
	//

	//// �̵��� �ʿ䰡 ����. ���� �����ִ°�
	//if (true == UEngineInput::GetInst().IsPress('A'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::LEFT * _DeltaTime * 100.0f);
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress('D'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 100.0f);
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress('W'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::UP * _DeltaTime * 100.0f);
	//}
	//
	//if (true == UEngineInput::GetInst().IsPress('S'))
	//{
	//	WallTileMap->AddActorLocation(FVector2D::DOWN * _DeltaTime * 100.0f);
	//}

}
