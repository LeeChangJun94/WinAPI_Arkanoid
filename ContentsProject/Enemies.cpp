#include "PreCompile.h"
#include "Enemies.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineMath.h>
#include "ContentsEnum.h"

AEnemies::AEnemies()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite(".png");
	SpriteRenderer->SetComponentScale({ 48, 48 });
	SpriteRenderer->SetOrder(ERenderOrder::ENEMIES);

	SpriteRenderer->CreateAnimation("Enemies_Type1", "Enemies_Type1.png", 0, 7, 0.2f);
	SpriteRenderer->CreateAnimation("Enemies_Type2", "Enemies_Type2.png", 0, 10, 0.2f);
	SpriteRenderer->CreateAnimation("Enemies_Type3", "Enemies_Type3.png", 0, 23, 0.2f);
	SpriteRenderer->CreateAnimation("Enemies_Type4", "Enemies_Type4.png", 0, 9, 0.2f);
	SpriteRenderer->CreateAnimation("Enemies_Destroy", "Enemies_Destroy.png", 0, 5, 0.2f);

	SpriteRenderer->ChangeAnimation("Enemies_Type1");

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 32, 32 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Enemies);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

AEnemies::~AEnemies()
{
}

void AEnemies::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemies::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
}

