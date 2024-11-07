#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bullet.png");
	SpriteRenderer->SetComponentScale({ 48, 24 });

	SpriteRenderer->CreateAnimation("Bullet", "Bullet.png", 0, 2, 0.1f);
	//SetActorScale({ 50, 50 });
}

ABullet::~ABullet()
{
}

void ABullet::Tick(float _DeltaTime)
{

	AddActorLocation(FVector2D::UP * _DeltaTime * 600.0f);



}