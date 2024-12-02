#include "PreCompile.h"
#include "TitleGameMode.h"
#include "Score.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"
#include "Intro.h"
#include "Score.h"
#include "Player.h"
#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
	
}

ATitleGameMode::~ATitleGameMode()
{
}



void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();

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
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	CheckTime += _DeltaTime;

	if (CheckTime > 0.3f)
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TitleBlack.png");
		SpriteRenderer->SetComponentScale({ 672, 168 });
		SpriteRenderer->SetComponentLocation({ 336, 384 });
	}
	if (CheckTime > 0.6f)
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Title2.png");
		SpriteRenderer->SetComponentScale({ 672, 168 });
		SpriteRenderer->SetComponentLocation({ 336, 384 });
		CheckTime = 0.0f;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_RETURN))
	{
		UEngineAPICore::GetCore()->ResetLevel<AIntro, AActor>("Intro");
		UEngineAPICore::GetCore()->OpenLevel("Intro");
	}
}

void ATitleGameMode::LevelChangeStart()
{
	Super::LevelChangeStart();
	APlayer::PlayerScore = 0;
}

void ATitleGameMode::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}