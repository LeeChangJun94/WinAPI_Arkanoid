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

	AIntro_Laser* Laser = GetWorld()->SpawnActor<AIntro_Laser>();
	Laser->SetActorLocation({ 440, 420 });

	Text = GetWorld()->SpawnActor<AText>();
	Text->SetTextSpriteName("Text");
	Text->SetOrder(ERenderOrder::UI);
	Text->SetTextScale({ 24, 24 });
	Text->SetActorLocation({ 48, 96 });
	Text->SetText("THESLDKJFL", 0.1f, false);
}


void AIntro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckTime += _DeltaTime;

	Text->ShowText(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('M'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage");
	}
}