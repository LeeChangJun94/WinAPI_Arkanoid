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
		this->Speed = 0.0f;
		SpriteRenderer->ChangeAnimation("BulletDone");
	}
}

void ABullet::AttackDone()
{
	if (true == this->IsDestroy())
	{
		return;
	}

	this->Destroy();
	//APlayer::Vaus->SetBulletCount(-1);
	std::list<ABullet*>& List = Player->GetBulletPtr();
	List.remove(this);

	///*std::list<ABullet*>::iterator*/auto StartIter = List.begin();
	///*std::list<ABullet*>::iterator*/auto EndIter = List.end();
	//for (; StartIter != EndIter; )
	//{
	//	if (this != *StartIter)
	//	{
	//		StartIter++;
	//		continue;
	//	}
	//
	//	List.erase(StartIter);
	//	break;
	//}
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	
	Attack();

	if (84 > GetActorLocation().Y)
	{
		this->Speed = 0.0f;
		//APlayer::Vaus->SetBulletCount(-1);
		SpriteRenderer->ChangeAnimation("BulletDone");
	}
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetPawn<APlayer>();
}
