#include "PreCompile.h"
#include "DeathLine.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"
#include "Ball.h"

ADeathLine::ADeathLine()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::DETHLINE);
	SpriteRenderer->SetSprite("DethLine.png");

	SpriteRenderer->SetComponentScale({ 672, 2 });
	SpriteRenderer->SetComponentLocation({ WindowSize.Half().X, WindowSize.Y - 1 });

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ WindowSize.Half().X, WindowSize.Y - 1 });
	CollisionComponent->SetComponentScale({ 672, 2 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::DethLine);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ADeathLine::~ADeathLine()
{
}
