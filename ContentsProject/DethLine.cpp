#include "PreCompile.h"
#include "DethLine.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"
#include "Ball.h"

ADethLine::ADethLine()
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

ADethLine::~ADethLine()
{
}

ABall* ADethLine::GetCollisionCheck()
{
	ABall* BallResult = reinterpret_cast<ABall*>(CollisionComponent->CollisionOnce(ECollisionGroup::Ball));
	return BallResult;
}

