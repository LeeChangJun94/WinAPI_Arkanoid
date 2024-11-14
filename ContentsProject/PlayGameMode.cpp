#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Player.h"
#include "PlayerLife.h"
#include "Fade.h"

#include "ContentsEnum.h"


APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//
	APlayMap* Stage1 = GetWorld()->SpawnActor<APlayMap>();

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

	ABall* BallActor = GetWorld()->SpawnActor<ABall>();
	APlayerLife* PlayerLifeActor = GetWorld()->SpawnActor<APlayerLife>();


	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			ABrick* Ptr = GetWorld()->SpawnActor<ABrick>();
			Ptr->SetActorLocation({ 48 + (48 * i), 160 + (24 * j) });
			Ptr->SetPlayerLife(PlayerLifeActor);
			//Ptr->SetBallActor(this->BallActor);

			BrickPtr.push_back(Ptr);
		}
	}
}

