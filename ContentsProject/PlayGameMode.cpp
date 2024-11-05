#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"

#include "ContentsEnum.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	//GameTileMap = GetWorld()->SpawnActor<ATileMap>();
	//
	//for (int y = 0; y < 5; y++)
	//{
	//	for (int x = 0; x < 10; x++)
	//	{
	//		GameTileMap->SetTileIndex({ y,x }, { 0, -6 }, { 32, 44 }, 2);
	//	}
	//}
	
	APlayMap* NewActor = GetWorld()->SpawnActor<APlayMap>();

	ABall* BallActor = GetWorld()->SpawnActor<ABall>();

	//BrickTileMap = GetWorld()->SpawnActor<ATileMap>();
	//BrickTileMap->Create("Bricks.png", { 10, 10 }, { 64, 32 });
	//
	//for (int x = 0; x < 10; ++x)
	//{
	//	for (int y = 0; y < 5; ++y)
	//	{
	//		BrickTileMap->SetTileIndex({ x, y}, {32 , 160}, {64, 32}, 0);
	//	}
	//}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
			Ptr->SetActorLocation({ 64 + (64 * i), 160 + (32 * j) });
		}
	}
	//ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();

	//{
	//	AScore* NewActor = GetWorld()->SpawnActor<AScore>();

	//	// NewActor->SetActorLocation({300, 300});
	//	NewActor->SetTextSpriteName("Text.bmp");
	//	NewActor->SetOrder(ERenderOrder::UI);
	//	NewActor->SetTextScale({ 50, 100 });
	//	NewActor->SetValue(45362784);

	//}

}