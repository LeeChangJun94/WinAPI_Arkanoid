#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

APlayMap::APlayMap()
{
	FVector2D WindowSize =  UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	
	USpriteRenderer* SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer1->SetSprite("Fields2.png");

	SpriteRenderer1->SetComponentScale({ 672, 720 });
	SpriteRenderer1->SetComponentLocation({ 336, 408 });
	
	USpriteRenderer* SpriteRenderer2 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer2->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer2->SetSprite("UI_TOP.png");

	SpriteRenderer2->SetComponentScale({ 672, 48 });
	SpriteRenderer2->SetComponentLocation({ 336, 24 });

}

APlayMap::~APlayMap()
{
}

