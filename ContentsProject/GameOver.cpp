#include "PreCompile.h"
#include "GameOver.h"
#include "PlayMap.h"
#include "Text.h"
#include "Number.h"
#include "Stage.h"
#include "ContentsEnum.h"
#include "TitleGameMode.h"
#include "Score.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

AGameOver::AGameOver()
{
}

AGameOver::~AGameOver()
{
}

void AGameOver::BeginPlay()
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

	APlayMap* Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(EPlayMapType::TYPE_DARK);

	Text1 = GetWorld()->SpawnActor<AText>();
	Text1->SetTextSpriteName("Text_Red");
	Text1->SetOrder(ERenderOrder::UI);
	Text1->SetTextScale({ 24, 24 });
	Text1->SetActorLocation({ 144, 120 });
	Text1->SetText("TO CONTINUE GAME", false);

	Text2 = GetWorld()->SpawnActor<AText>();
	Text2->SetTextSpriteName("Text_White");
	Text2->SetOrder(ERenderOrder::UI);
	Text2->SetTextScale({ 24, 24 });
	Text2->SetActorLocation({ 24, 216 });
	Text2->SetText("IF YOU DO LIKE TO", false);

	Text3 = GetWorld()->SpawnActor<AText>();
	Text3->SetTextSpriteName("Text_White");
	Text3->SetOrder(ERenderOrder::UI);
	Text3->SetTextScale({ 24, 24 });
	Text3->SetActorLocation({ 24, 264 });
	Text3->SetText("TRY AGAIN, PLEASE PRESS \"A\"", false);

	Text4 = GetWorld()->SpawnActor<AText>();
	Text4->SetTextSpriteName("Text_White");
	Text4->SetOrder(ERenderOrder::UI);
	Text4->SetTextScale({ 24, 24 });
	Text4->SetActorLocation({ 24, 312 });
	Text4->SetText("BUTTON TO RESTART THE GAME.", false);
	
	Text5 = GetWorld()->SpawnActor<AText>();
	Text5->SetTextSpriteName("Text_White");
	Text5->SetOrder(ERenderOrder::UI);
	Text5->SetTextScale({ 24, 24 });
	Text5->SetActorLocation({ 144, 408 });
	Text5->SetText("BEFFORE", false);

	Text6 = GetWorld()->SpawnActor<AText>();
	Text6->SetTextSpriteName("Text_White");
	Text6->SetOrder(ERenderOrder::UI);
	Text6->SetTextScale({ 24, 24 });
	Text6->SetActorLocation({ 144, 456 });
	Text6->SetText("TIMER REACHES \"0\".", false);

	Text7 = GetWorld()->SpawnActor<AText>();
	Text7->SetTextSpriteName("Text_Yellow");
	Text7->SetOrder(ERenderOrder::UI);
	Text7->SetTextScale({ 24, 24 });
	Text7->SetActorLocation({ 240, 552 });
	Text7->SetText("TIME", false);

	Text8 = GetWorld()->SpawnActor<AText>();
	Text8->SetTextSpriteName("Text_Yellow");
	Text8->SetOrder(ERenderOrder::UI);
	Text8->SetTextScale({ 24, 24 });
	Text8->SetActorLocation({ 384, 552 });
	Text8->SetText(Time, false);

	Text9 = GetWorld()->SpawnActor<AText>();
	Text9->SetTextSpriteName("Text_White");
	Text9->SetOrder(ERenderOrder::UI);
	Text9->SetTextScale({ 24, 24 });
	Text9->SetActorLocation({ 240, 552 });
	Text9->SetText("GAME OVER", false);

	Text9->SetActive(false);
}

void AGameOver::Tick(float _Deltatime)
{
	Super::Tick(_Deltatime);

	CheckTime += _Deltatime;

	if (10.0f > CheckTime)
	{
		if (true == UEngineInput::GetInst().IsDown('A'))
		{
			if (33 != AStage::Stage)
			{
				UEngineAPICore::GetCore()->OpenLevel("Stage");
			}
			else
			{
				UEngineAPICore::GetCore()->OpenLevel("Stage_Boss");
			}
		}

		Text8->SetText(static_cast<int>(Time - CheckTime), false);
		return;
	}

	if (true != GameOver)
	{
		GameOver = true;

		Text1->SetActive(false);
		Text2->SetActive(false);
		Text3->SetActive(false);
		Text4->SetActive(false);
		Text5->SetActive(false);
		Text6->SetActive(false);
		Text7->SetActive(false);
		Text8->SetActive(false);
		Text9->SetActive(true);
		GameOverSound = UEngineSound::Play("05 Game Over.mp3");
		GameOverSound.SetVolume(0.2f);

		TimeEventer.PushEvent(3.0f, [this]()
			{
				UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
				UEngineAPICore::GetCore()->OpenLevel("Title");
			});
	}
}

