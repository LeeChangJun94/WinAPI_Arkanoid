#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"
#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Item.h"
#include "Score.h"


#include <EngineCore/ImageManager.h>
#include <EngineBase/EngineRandom.h>


ABrick::ABrick()
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

	//SpriteRenderer->ChangeAnimation("Silver");

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 48, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Brick);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
} 

ABrick::~ABrick()
{
}


void ABrick::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();

	switch (BrickType)
	{
	case EBrickType::WHITE:
		WhiteBrick();
		break;
	case EBrickType::ORANGE:
		OrangeBrick();
		break;
	case EBrickType::SKYBLUE:
		SkyBlueBrick();
		break;
	case EBrickType::GREEN:
		GreenBrick();
		break;
	case EBrickType::RED:
		RedBrick();
		break;
	case EBrickType::BLUE:
		BlueBrick();
		break;
	case EBrickType::PINK:
		PinkBrick();
		break;
	case EBrickType::YELLOW:
		YellowBrick();
		break;
	case EBrickType::SILVER:
		SilverBrick();
		break;
	case EBrickType::GOLD:
		GoldBrick();
		break;
	default:
		break;
	}
}

void ABrick::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BrickTrans.Location = { GetActorLocation() };

	FVector2D BrickSize = SpriteRenderer->GetComponentScale();

	Ratio = (BrickSize.Y / 2) / (BrickSize.X / 2);

	ResultBall = reinterpret_cast<ABall*>(CollisionComponent->CollisionOnce(ECollisionGroup::Ball));

	if (nullptr != ResultBall)
	{
		BallTrans.Location = { ResultBall->GetActorLocation() };
		//Brick 왼쪽
		if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X >(BrickTrans.Location.X - (BrickSize.X / 2)) &&
			BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}

		if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X >(BrickTrans.Location.X - (BrickSize.X / 2)) &&
			BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickSize.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}


		//Brick 오른쪽
		if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
			BallTrans.Location.Y >(BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}

		if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
			BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickSize.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect();

					BrickDestroyCheck();
				}
			}
		}
	}
}

// 데이터를 직렬화(압축)
void ABrick::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	//_Ser << BrickType;

}
// 데이터를 복구(할때)
void ABrick::DeSerialize(UEngineSerializer& _Ser)
{
	int a = 0;
}


void ABrick::BrickDestroyCheck()
{
	BrickHP -= 1;

	if (0 == BrickHP)
	{
		this->Destroy();

		AItem* Ptr = GetWorld()->SpawnActor<AItem>();
		Ptr->SetActorLocation(GetActorLocation());
		Ptr->SetPlayerLife(PlayerLife);
		Ptr->SetBall(ResultBall);

		Vaus->AddPlayerScore(Score);
	}
}

void ABrick::BallReflect()
{
	FVector2D Dir;
	Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

	ResultBall->SetBallDir(Dir);
}

void ABrick::WhiteBrick()
{
	SpriteRenderer->ChangeAnimation("White");
	Score = 50;
	BrickHP = 1;
}

void ABrick::OrangeBrick()
{
	SpriteRenderer->ChangeAnimation("Orange");
	Score = 60;
	BrickHP = 1;
}

void ABrick::SkyBlueBrick()
{
	SpriteRenderer->ChangeAnimation("SkyBlue");
	Score = 70;
	BrickHP = 1;
}

void ABrick::GreenBrick()
{
	SpriteRenderer->ChangeAnimation("Green");
	Score = 80;
	BrickHP = 1;
}

void ABrick::RedBrick()
{
	SpriteRenderer->ChangeAnimation("Red");
	Score = 90;
	BrickHP = 1;
}

void ABrick::BlueBrick()
{
	SpriteRenderer->ChangeAnimation("Blue");
	Score = 100;
	BrickHP = 1;
}

void ABrick::PinkBrick()
{
	SpriteRenderer->ChangeAnimation("Pink");
	Score = 110;
	BrickHP = 1;
}

void ABrick::YellowBrick()
{
	SpriteRenderer->ChangeAnimation("Yellow");
	Score = 120;
	BrickHP = 1;
}

void ABrick::SilverBrick()
{
	SpriteRenderer->ChangeAnimation("Silver");
	Score = 50;
	BrickHP = 2;
}

void ABrick::GoldBrick()
{
	SpriteRenderer->ChangeAnimation("Gold");
	Score = 0;
	BrickHP = -1;
}


