#include "PreCompile.h"
#include "Intro.h"
#include "Score.h"
#include "PlayMap.h"
#include "Intro_Laser.h"
#include "Text.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"

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
	
	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();
	Map = GetWorld()->SpawnActor<APlayMap>();
	Map->SetPlayMapType(EPlayMapType::TYPE_INTRO);

	TimeEventer.PushEvent(4.1f, [this]()
		{
			AIntro_Laser* Laser = GetWorld()->SpawnActor<AIntro_Laser>();
			Laser->SetActorLocation({ 440, 420 });
		});

	Text1 = GetWorld()->SpawnActor<AText>();
	Text1->SetTextSpriteName("Text");
	Text1->SetOrder(ERenderOrder::UI);
	Text1->SetTextScale({ 24, 24 });
	Text1->SetActorLocation({ 48, 96 });
	Text1->SetText("THE ERA AND TIME OF", 0.1f, false);

	Text2 = GetWorld()->SpawnActor<AText>();
	Text2->SetTextSpriteName("Text");
	Text2->SetOrder(ERenderOrder::UI);
	Text2->SetTextScale({ 24, 24 });
	Text2->SetActorLocation({ 48, 144 });
	Text2->SetText("THIS STORY IS UNKNOWN.", 0.1f, false);
	
	TimeEventer.PushEvent(4.2f, [this]()
		{
			Text1->SetActive(false);
			Text2->SetActive(false);
		});

	Text3 = GetWorld()->SpawnActor<AText>();
	Text3->SetTextSpriteName("Text");
	Text3->SetOrder(ERenderOrder::UI);
	Text3->SetTextScale({ 24, 24 });
	Text3->SetActorLocation({ 48, 96 });
	Text3->SetText("AFTER THE MOTHERSHIP", 0.1f, false);

	Text4 = GetWorld()->SpawnActor<AText>();
	Text4->SetTextSpriteName("Text");
	Text4->SetOrder(ERenderOrder::UI);
	Text4->SetTextScale({ 24, 24 });
	Text4->SetActorLocation({ 48, 144 });
	Text4->SetText("\"ARKANOID\" WAS DESTROYED,", 0.1f, false);

	Text5 = GetWorld()->SpawnActor<AText>();
	Text5->SetTextSpriteName("Text");
	Text5->SetOrder(ERenderOrder::UI);
	Text5->SetTextScale({ 24, 24 });
	Text5->SetActorLocation({ 48, 192 });
	Text5->SetText("A SPACECRAFT \"VAUS\"", 0.1f, false);

	Text6 = GetWorld()->SpawnActor<AText>();
	Text6->SetTextSpriteName("Text");
	Text6->SetOrder(ERenderOrder::UI);
	Text6->SetTextScale({ 24, 24 });
	Text6->SetActorLocation({ 48, 240 });
	Text6->SetText("SCRAMBLED AWAY FROM IT.", 0.1f, false);
}


void AIntro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckTime += _DeltaTime;

	Text1->ShowText(_DeltaTime);

	if (1.9f < CheckTime)
	{
		Text2->ShowText(_DeltaTime);
	}

	if (4.3f < CheckTime)
	{
		Text3->ShowText(_DeltaTime);
	}
	
	if (6.4f < CheckTime)
	{
		Text4->ShowText(_DeltaTime);
	}

	if (9.0f < CheckTime)
	{
		Text5->ShowText(_DeltaTime);
	}

	if (11.0f < CheckTime)
	{
		Text6->ShowText(_DeltaTime);
	}

	if (true == UEngineInput::GetInst().IsDown('M'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage");
	}
}