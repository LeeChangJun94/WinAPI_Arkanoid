#include "PreCompile.h"
#include "Intro.h"
#include "Score.h"
#include "PlayMap.h"
#include "InOuttro_Laser.h"
#include "Text.h"
#include "InOuttro_Vaus.h"
#include "InOuttro_StarShip.h"
#include "InOuttro_Enemies.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"
#include "TitleGameMode.h"
#include "Stage.h"
#include "Score.h"

#include "TitleLogo.h"

AIntro::AIntro()
{
	
}

AIntro::~AIntro()
{
}

void AIntro::BeginPlay()
{
	Super::BeginPlay();
	
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

	BGMPlayer = UEngineSound::Play("01 Story.mp3");
	BGMPlayer.SetVolume(0.2f);
	
	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();
	Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(EPlayMapType::TYPE_SPACE);

	Text1 = GetWorld()->SpawnActor<AText>();
	Text1->SetTextSpriteName("Text_White");
	Text1->SetOrder(ERenderOrder::UI);
	Text1->SetTextScale({ 24, 24 });
	Text1->SetActorLocation({ 48, 96 });
	Text1->SetText("THE ERA AND TIME OF", 0.1f, false);

	Text2 = GetWorld()->SpawnActor<AText>();
	Text2->SetTextSpriteName("Text_White");
	Text2->SetOrder(ERenderOrder::UI);
	Text2->SetTextScale({ 24, 24 });
	Text2->SetActorLocation({ 48, 144 });
	Text2->SetText("THIS STORY IS UNKNOWN.", 0.1f, false);
	
	TimeEventer.PushEvent(4.4f, [this]()
		{
			Text1->SetActive(false);
			Text2->SetActive(false);
		});

	Text3 = GetWorld()->SpawnActor<AText>();
	Text3->SetTextSpriteName("Text_White");
	Text3->SetOrder(ERenderOrder::UI);
	Text3->SetTextScale({ 24, 24 });
	Text3->SetActorLocation({ 48, 96 });
	Text3->SetText("AFTER THE MOTHERSHIP", 0.1f, false);

	Text4 = GetWorld()->SpawnActor<AText>();
	Text4->SetTextSpriteName("Text_White");
	Text4->SetOrder(ERenderOrder::UI);
	Text4->SetTextScale({ 24, 24 });
	Text4->SetActorLocation({ 48, 144 });
	Text4->SetText("\"ARKANOID\" WAS DESTROYED,", 0.1f, false);

	Text5 = GetWorld()->SpawnActor<AText>();
	Text5->SetTextSpriteName("Text_White");
	Text5->SetOrder(ERenderOrder::UI);
	Text5->SetTextScale({ 24, 24 });
	Text5->SetActorLocation({ 48, 192 });
	Text5->SetText("A SPACECRAFT \"VAUS\"", 0.1f, false);

	Text6 = GetWorld()->SpawnActor<AText>();
	Text6->SetTextSpriteName("Text_White");
	Text6->SetOrder(ERenderOrder::UI);
	Text6->SetTextScale({ 24, 24 });
	Text6->SetActorLocation({ 48, 240 });
	Text6->SetText("SCRAMBLED AWAY FROM IT.", 0.1f, false);
	
	TimeEventer.PushEvent(14.0f, [this]()
		{
			Text3->SetActive(false);
			Text4->SetActive(false);
			Text5->SetActive(false);
			Text6->SetActive(false);
		});

	Text7 = GetWorld()->SpawnActor<AText>();
	Text7->SetTextSpriteName("Text_White");
	Text7->SetOrder(ERenderOrder::UI);
	Text7->SetTextScale({ 24, 24 });
	Text7->SetActorLocation({ 48, 96 });
	Text7->SetText("BUT ONLY TO BE", 0.1f, false);

	Text8 = GetWorld()->SpawnActor<AText>();
	Text8->SetTextSpriteName("Text_White");
	Text8->SetOrder(ERenderOrder::UI);
	Text8->SetTextScale({ 24, 24 });
	Text8->SetActorLocation({ 48, 144 });
	Text8->SetText("TRAPPED IN SPACE WARPED", 0.1f, false);

	Text9 = GetWorld()->SpawnActor<AText>();
	Text9->SetTextSpriteName("Text_White");
	Text9->SetOrder(ERenderOrder::UI);
	Text9->SetTextScale({ 24, 24 });
	Text9->SetActorLocation({ 48, 192 });
	Text9->SetText("BY SOMEONE........", 0.1f, false);

	StarShip = GetWorld()->SpawnActor<AInOuttro_StarShip>();
	StarShip->SetActorLocation({ 303, 600 });
	StarShip->SetInOuttroType(EInOuttro_StarShip::INTRO);

	TimeEventer.PushEvent(2.0f, [this]()
		{
			AInOuttro_Enemies* Enemies = GetWorld()->SpawnActor<AInOuttro_Enemies>();
			Enemies->SetStarShip(StarShip);
			Enemies->SetInOuttroType(EInOuttro_Enemies::INTRO);
		});
}


void AIntro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));

	CheckTime += _DeltaTime;

	Text1->ShowText(_DeltaTime);

	if (1.9f < CheckTime)
	{
		Text2->ShowText(_DeltaTime);
	}

	if (4.5f < CheckTime)
	{
		Text3->ShowText(_DeltaTime);
	}
	
	if (6.6f < CheckTime)
	{
		Text4->ShowText(_DeltaTime);
	}

	if (9.2f < CheckTime)
	{
		Text5->ShowText(_DeltaTime);
	}

	if (11.2f < CheckTime)
	{
		Text6->ShowText(_DeltaTime);
	}

	if (14.1f < CheckTime)
	{
		Text7->ShowText(_DeltaTime);
	}

	if (15.6f < CheckTime)
	{
		Text8->ShowText(_DeltaTime);
	}

	if (18.0f < CheckTime)
	{
		Text9->ShowText(_DeltaTime);
	}

	if (21.0f < CheckTime)
	{
		BGMPlayer.Stop();
		AStage::Stage = 1;
		UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SUBTRACT))
	{
		BGMPlayer.Stop();
		UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_RETURN))
	{
		BGMPlayer.Stop();
		AStage::Stage = 1;
		UEngineAPICore::GetCore()->OpenLevel("Stage_Dark");
	}
}