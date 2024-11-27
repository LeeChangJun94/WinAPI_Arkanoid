#include "PreCompile.h"
#include "TitleGameMode.h"
#include "Score.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"
#include "Intro.h"

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