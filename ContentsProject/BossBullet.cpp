#include "PreCompile.h"
#include "BossBullet.h"
#include "Player.h"
#include "Stage_Boss.h"
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineMath.h>
#include "ContentsEnum.h"

ABossBullet::ABossBullet()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("BossBullet.png");
	SpriteRenderer->SetComponentScale({ 24, 24 });
	SpriteRenderer->CreateAnimation("BossBullet", "BossBullet.png", 0, 7, 0.1f);
	//SpriteRenderer->CreateAnimation("BulletDone", "Bullet.png", 0, 2, 0.1f);

	SpriteRenderer->ChangeAnimation("BossBullet");

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 24, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::BossBullet);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ABossBullet::~ABossBullet()
{
}

void ABossBullet::Attack()
{
	APlayer* VausResult = reinterpret_cast<APlayer*>(CollisionComponent->CollisionOnce(ECollisionGroup::Vaus));
	
	if (nullptr != VausResult)
	{
		AStage_Boss* Stage_Boss = reinterpret_cast<AStage_Boss*>(GetWorld()->GetGameMode());
		Stage_Boss->StageResetSetting();
		//Vaus->ChangeState(PlayerState::Destroy);
	}
}

//void ABossBullet::AttackDone()
//{
//	if (true == this->IsDestroy())
//	{
//		return;
//	}
//
//	this->Destroy();
//
//	std::list<ABossBullet*>& List = Vaus->GetBulletPtr();
//	List.remove(this);
//
//}

void ABossBullet::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();

	Dir = Vaus->GetActorLocation() - GetActorLocation();
	Dir.Normalize();
	//SetActorLocation(Vaus->GetActorLocation());
}

void ABossBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(Dir * _DeltaTime * Speed);

	Attack();

	if (5 == static_cast<int>(Vaus->GetCurPlayerState()))
	{
		this->Destroy();
	}
	/*if (84 > GetActorLocation().Y)
	{
		this->Speed = 0.0f;
		SpriteRenderer->ChangeAnimation("BulletDone");
	}
	*/
}

