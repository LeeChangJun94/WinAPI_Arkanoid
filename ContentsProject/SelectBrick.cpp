#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "SelectBrick.h"
#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Item.h"
#include "Score.h"


#include <EngineCore/ImageManager.h>
#include <EngineBase/EngineRandom.h>

ASelectBrick::ASelectBrick()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bricks.png");
	SpriteRenderer->SetComponentScale({ 48, 24 });

	SpriteRenderer->CreateAnimation("White", "Bricks.png", 0, 0, 0.0f);
	SpriteRenderer->CreateAnimation("Orange", "Bricks.png", 1, 1, 0.0f);
	SpriteRenderer->CreateAnimation("Skyblue", "Bricks.png", 2, 2, 0.0f);
	SpriteRenderer->CreateAnimation("Green", "Bricks.png", 3, 3, 0.0f);
	SpriteRenderer->CreateAnimation("Red", "Bricks.png", 6, 6, 0.0f);
	SpriteRenderer->CreateAnimation("Blue", "Bricks.png", 7, 7, 0.0f);
	SpriteRenderer->CreateAnimation("Pink", "Bricks.png", 8, 8, 0.0f);
	SpriteRenderer->CreateAnimation("Yellow", "Bricks.png", 9, 9, 0.0f);
	SpriteRenderer->CreateAnimation("Silver", "Bricks.png", 12, 17, 0.2f);
	SpriteRenderer->CreateAnimation("Gold", "Bricks.png", 18, 23, 0.2f);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 48, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Brick);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ASelectBrick::~ASelectBrick()
{
}


void ASelectBrick::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();

	switch (BrickType)
	{
	case ABrick::EBrickType::WHITE:
		WhiteBrick();
		break;
	case ABrick::EBrickType::ORANGE:
		OrangeBrick();
		break;
	case ABrick::EBrickType::SKYBLUE:
		SkyBlueBrick();
		break;
	case ABrick::EBrickType::GREEN:
		GreenBrick();
		break;
	case ABrick::EBrickType::RED:
		RedBrick();
		break;
	case ABrick::EBrickType::BLUE:
		BlueBrick();
		break;
	case ABrick::EBrickType::PINK:
		PinkBrick();
		break;
	case ABrick::EBrickType::YELLOW:
		YellowBrick();
		break;
	case ABrick::EBrickType::SILVER:
		SilverBrick();
		break;
	case ABrick::EBrickType::GOLD:
		GoldBrick();
		break;
	default:
		break;
	}
}

void ASelectBrick::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ASelectBrick::WhiteBrick()
{
	SpriteRenderer->ChangeAnimation("White");
	Score = 50;
	BrickHP = 1;
}

void ASelectBrick::OrangeBrick()
{
	SpriteRenderer->ChangeAnimation("Orange");
	Score = 60;
	BrickHP = 1;
}

void ASelectBrick::SkyBlueBrick()
{
	SpriteRenderer->ChangeAnimation("SkyBlue");
	Score = 70;
	BrickHP = 1;
}

void ASelectBrick::GreenBrick()
{
	SpriteRenderer->ChangeAnimation("Green");
	Score = 80;
	BrickHP = 1;
}

void ASelectBrick::RedBrick()
{
	SpriteRenderer->ChangeAnimation("Red");
	Score = 90;
	BrickHP = 1;
}

void ASelectBrick::BlueBrick()
{
	SpriteRenderer->ChangeAnimation("Blue");
	Score = 100;
	BrickHP = 1;
}

void ASelectBrick::PinkBrick()
{
	SpriteRenderer->ChangeAnimation("Pink");
	Score = 110;
	BrickHP = 1;
}

void ASelectBrick::YellowBrick()
{
	SpriteRenderer->ChangeAnimation("Yellow");
	Score = 120;
	BrickHP = 1;
}

void ASelectBrick::SilverBrick()
{
	SpriteRenderer->ChangeAnimation("Silver");
	Score = 50;
	BrickHP = 2;
}

void ASelectBrick::GoldBrick()
{
	SpriteRenderer->ChangeAnimation("Gold");
	Score = 0;
	BrickHP = -1;
}


