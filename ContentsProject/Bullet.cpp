#include "PreCompile.h"
#include "Bullet.h"
#include "Player.h"
#include "Brick.h"
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
	ABrick* BrickResult = reinterpret_cast<ABrick*>(CollisionComponent->CollisionOnce(ECollisionGroup::Brick));
	if (nullptr != BrickResult)
	{
		if (0 != AttackCheck)
		{
			BrickResult->BrickDestroyCheck();
			//this->SetActorLocation({ GetActorLocation().X, GetActorLocation().Y});
			this->Speed = 0.0f;
			SpriteRenderer->ChangeAnimation("BulletDone");
			AttackCheck -= 1;
		}
	}
}

void ABullet::AttackDone()
{
	if (true == this->IsDestroy())
	{
		return;
	}

	this->Destroy();

	std::list<ABullet*>& List = Vaus->GetBulletPtr();
	List.remove(this);

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();

	SetActorLocation(Vaus->GetActorLocation());
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	
	Attack();

	if (84 > GetActorLocation().Y)
	{
		this->Speed = 0.0f;
		SpriteRenderer->ChangeAnimation("BulletDone");
	}
}

