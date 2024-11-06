#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bullet.png");
	SpriteRenderer->SetComponentScale({ 48, 72 });

	//SetActorScale({ 50, 50 });
}

ABullet::~ABullet()
{
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(FVector2D::UP * _DeltaTime * 600.0f);
}