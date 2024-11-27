#include "PreCompile.h"
#include "BossBullet.h"
#include "Player.h"
#include "Stage_Boss.h"
#include "Boss.h"
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineMath.h>
#include "ContentsEnum.h"

ABossBullet::ABossBullet()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 24, 24 });
	SpriteRenderer->CreateAnimation("BossBullet", "BossBullet.png", 0, 7, 0.1f);

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
		AStage_Boss* Stage_Boss = GetWorld()->GetGameMode<AStage_Boss>();
		Stage_Boss->StageResetSetting();
	}
}

void ABossBullet::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();

	Dir = Vaus->GetActorLocation() - GetActorLocation();
	Dir.Normalize();
}

void ABossBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(Dir * _DeltaTime * Speed);

	Attack();

	if (PlayerState::Destroy == Vaus->GetCurPlayerState())
	{
		this->Destroy();
	}
}

