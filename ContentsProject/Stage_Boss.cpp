#include "PreCompile.h"
#include "Stage_Boss.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Player.h"
#include "PlayerLife.h"
#include "Fade.h"
#include "DethLine.h"
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

AStage_Boss::AStage_Boss()
{
	//243, 120
}

AStage_Boss::~AStage_Boss()
{
}

void AStage_Boss::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();

	APlayMap* BossStage = GetWorld()->SpawnActor<APlayMap>();
	BossStage->SetPlayMapType(EPlayMapType::TYPE_BOSS);

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
}

void AStage_Boss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('N'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage_032");
	}

	/*if (true == UEngineInput::GetInst().IsDown('M'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage_003");
	}*/
}



