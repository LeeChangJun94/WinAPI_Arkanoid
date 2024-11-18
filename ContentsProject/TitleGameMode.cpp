#include "PreCompile.h"
#include "TitleGameMode.h"
#include "Score.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"

#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}


// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void ATitleGameMode::BeginPlay()
{

	Super::BeginPlay();
	TitleLogo* NewActor = GetWorld()->SpawnActor<TitleLogo>();

}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//UEngineDebug::CoreOutPutString("DeltaTime : " + std::to_string(CheckTime));
	
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

	
	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Stage1");
	}
}