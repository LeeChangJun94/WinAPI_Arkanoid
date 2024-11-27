#include "PreCompile.h"
#include "Outtro.h"
#include "Score.h"
#include "PlayMap.h"
#include "Text.h"
#include "Ending_Vaus.h"
#include "InOuttro_StarShip.h"
#include "InOuttro_Vaus.h"
#include "InOuttro_Enemies.h"
#include "Player.h"
#include "Stage_Boss.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"

#include "TitleLogo.h"

AOuttro::AOuttro()
{
}

AOuttro::~AOuttro()
{
}

void AOuttro::BeginPlay()
{
	Super::BeginPlay();

	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();
	Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(EPlayMapType::TYPE_SPACE);

	TimeEventer.PushEvent(0.5f, [this]()
		{
			AInOuttro_Enemies* Outtro_Vaus = GetWorld()->SpawnActor<AInOuttro_Enemies>();
			Outtro_Vaus->SetInOuttroType(EInOuttro_Enemies::OUTTRO);
			Outtro_Vaus->SetStarShip(StarShip);
		});

	TimeEventer.PushEvent(9.2f, [this]()
		{
			AInOuttro_Vaus* Outtro_Vaus = GetWorld()->SpawnActor<AInOuttro_Vaus>();
			Outtro_Vaus->SetInOuttroType(EInOuttro_Vaus::OUTTRO);
		});

	Text1 = GetWorld()->SpawnActor<AText>();
	Text1->SetTextSpriteName("Text_White");
	Text1->SetOrder(ERenderOrder::UI);
	Text1->SetTextScale({ 24, 24 });
	Text1->SetActorLocation({ 48, 96 });
	Text1->SetText("DIMENSION CONTROLLING FORT", 0.1f, false);

	Text2 = GetWorld()->SpawnActor<AText>();
	Text2->SetTextSpriteName("Text_White");
	Text2->SetOrder(ERenderOrder::UI);
	Text2->SetTextScale({ 24, 24 });
	Text2->SetActorLocation({ 48, 144 });
	Text2->SetText("\"DOH\" HAS NOW BEEN", 0.1f, false);

	Text3 = GetWorld()->SpawnActor<AText>();
	Text3->SetTextSpriteName("Text_White");
	Text3->SetOrder(ERenderOrder::UI);
	Text3->SetTextScale({ 24, 24 });
	Text3->SetActorLocation({ 48, 192 });
	Text3->SetText("DEMOLISHED, AND TIME", 0.1f, false);

	Text4 = GetWorld()->SpawnActor<AText>();
	Text4->SetTextSpriteName("Text_White");
	Text4->SetOrder(ERenderOrder::UI);
	Text4->SetTextScale({ 24, 24 });
	Text4->SetActorLocation({ 48, 240 });
	Text4->SetText("STARTED FLOWING REVERSELY.", 0.1f, false);

	TimeEventer.PushEvent(9.3f, [this]()
		{
			Text1->SetActive(false);
			Text2->SetActive(false);
			Text3->SetActive(false);
			Text4->SetActive(false);
		});

	Text5 = GetWorld()->SpawnActor<AText>();
	Text5->SetTextSpriteName("Text_White");
	Text5->SetOrder(ERenderOrder::UI);
	Text5->SetTextScale({ 24, 24 });
	Text5->SetActorLocation({ 48, 96 });
	Text5->SetText("\"VAUS\" MANAGED TO ESCAPE", 0.1f, false);

	Text6 = GetWorld()->SpawnActor<AText>();
	Text6->SetTextSpriteName("Text_White");
	Text6->SetOrder(ERenderOrder::UI);
	Text6->SetTextScale({ 24, 24 });
	Text6->SetActorLocation({ 48, 144 });
	Text6->SetText("FROM THE DISTORTED SPACE.", 0.1f, false);

	TimeEventer.PushEvent(13.7f, [this]()
		{
			Text5->SetActive(false);
			Text6->SetActive(false);
		});

	Text7 = GetWorld()->SpawnActor<AText>();
	Text7->SetTextSpriteName("Text_White");
	Text7->SetOrder(ERenderOrder::UI);
	Text7->SetTextScale({ 24, 24 });
	Text7->SetActorLocation({ 48, 96 });
	Text7->SetText("BUT THE REAL VOYAGE OF", 0.1f, false);

	Text8 = GetWorld()->SpawnActor<AText>();
	Text8->SetTextSpriteName("Text_White");
	Text8->SetOrder(ERenderOrder::UI);
	Text8->SetTextScale({ 24, 24 });
	Text8->SetActorLocation({ 48, 144 });
	Text8->SetText("\"ARKANOID\" IN THE GALAXY", 0.1f, false);

	Text9 = GetWorld()->SpawnActor<AText>();
	Text9->SetTextSpriteName("Text_White");
	Text9->SetOrder(ERenderOrder::UI);
	Text9->SetTextScale({ 24, 24 });
	Text9->SetActorLocation({ 48, 192 });
	Text9->SetText("HAS ONLY STARTED......", 0.1f, false);

	StarShip = GetWorld()->SpawnActor<AInOuttro_StarShip>();
	StarShip->SetActorLocation({ 303, 600 });
	StarShip->SetInOuttroType(EInOuttro_StarShip::OUTTRO);

	TimeEventer.PushEvent(12.7f, [this]()
		{
			StarShip->GetSpriteRenderer()->ChangeAnimation("StarShip_Open");
		});

	TimeEventer.PushEvent(22.0f, [this]()
		{
			UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
			UEngineAPICore::GetCore()->OpenLevel("Title");
		});
}


void AOuttro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckTime += _DeltaTime;

	Text1->ShowText(_DeltaTime);

	if (2.6f < CheckTime)
	{
		Text2->ShowText(_DeltaTime);
	}

	if (4.4f < CheckTime)
	{
		Text3->ShowText(_DeltaTime);
	}

	if (6.5f < CheckTime)
	{
		Text4->ShowText(_DeltaTime);
	}

	if (9.3f < CheckTime)
	{
		Text5->ShowText(_DeltaTime);
	}

	if (11.0f < CheckTime)
	{
		Text6->ShowText(_DeltaTime);
	}

	if (13.7f < CheckTime)
	{
		Text7->ShowText(_DeltaTime);
	}

	if (15.0f < CheckTime)
	{
		Text8->ShowText(_DeltaTime);
	}

	if (17.5f < CheckTime)
	{
		Text9->ShowText(_DeltaTime);
	}

	if (true == UEngineInput::GetInst().IsDown(VK_SUBTRACT))
	{
		UEngineAPICore::GetCore()->ResetLevel<AStage_Boss, APlayer>("Stage_Boss");
		UEngineAPICore::GetCore()->OpenLevel("Stage_Boss");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_ADD))
	{
			UEngineAPICore::GetCore()->ResetLevel<ATitleGameMode, AActor>("Title");
			UEngineAPICore::GetCore()->OpenLevel("Title");
	}
}