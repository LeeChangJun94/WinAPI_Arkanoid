#include "PreCompile.h"
#include "Bullet.h"
#include "Player.h"
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

ABullet::ABullet()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bullet.png");
	SpriteRenderer->SetComponentScale({ 48, 24 });
	SpriteRenderer->CreateAnimation("Bullet", "Bullet.png", 0, 0);
	SpriteRenderer->CreateAnimation("BulletDone", "Bullet.png", 0, 2, 0.1f);
	SpriteRenderer->SetAnimationEvent("BulletDone", 2, std::bind(&ABullet::AttackDone, this));
	
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 48, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Bullet);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ABullet::~ABullet()
{
}

void ABullet::Attack()
{
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Brick);
	if (nullptr != Result)
	{
		Result->Destroy();
		SpriteRenderer->ChangeAnimation("BulletDone");
		this->Speed = 0.0f;
	}
}

void ABullet::AttackDone()
{
	this->Destroy();
	std::list<ABullet*>& List = APlayer::Vaus->GetBulletPtr();
	std::list<ABullet*>::iterator StartIter = List.begin();
	std::list<ABullet*>::iterator EndIter = List.end();
	for (; StartIter != EndIter; )
	{
		if (this != *StartIter)
		{
			StartIter++;
		}
	
		List.erase(StartIter);
		break;
	}
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	
	Attack();

	if (84 > GetActorLocation().Y)
	{
		SpriteRenderer->ChangeAnimation("BulletDone");
		this->Speed = 0.0f;
	}
}