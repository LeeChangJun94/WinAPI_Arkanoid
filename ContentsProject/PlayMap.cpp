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

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("Fields2.png");

		SpriteRenderer->SetComponentScale({ 896, 960 });
		SpriteRenderer->SetComponentLocation({ 448, 544 });
	}
	
	//SetSprite("Fields2.png");
}

APlayMap::~APlayMap()
{
}

