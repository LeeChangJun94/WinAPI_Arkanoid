#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

TitleLogo::TitleLogo()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("Title1.png");

	SpriteRenderer->SetComponentScale(WindowSize);
	SpriteRenderer->SetComponentLocation(WindowSize.Half());


}

TitleLogo::~TitleLogo()
{
}

