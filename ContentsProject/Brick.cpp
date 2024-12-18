#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ContentsEnum.h"
#include "Stage.h"
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
	
	SpriteRenderer->CreateAnimation("White", "Bricks.png", 0, 0, 0.0f, false);
	SpriteRenderer->CreateAnimation("Orange", "Bricks.png", 1, 1, 0.0f, false);
	SpriteRenderer->CreateAnimation("Skyblue", "Bricks.png", 2, 2, 0.0f, false);
	SpriteRenderer->CreateAnimation("Green", "Bricks.png", 3, 3, 0.0f, false);
	SpriteRenderer->CreateAnimation("Red", "Bricks.png", 6, 6, 0.0f, false);
	SpriteRenderer->CreateAnimation("Blue", "Bricks.png", 7, 7, 0.0f, false);
	SpriteRenderer->CreateAnimation("Pink", "Bricks.png", 8, 8, 0.0f, false);
	SpriteRenderer->CreateAnimation("Yellow", "Bricks.png", 9, 9, 0.0f, false);
	SpriteRenderer->CreateAnimation("Silver_Idle", "Bricks.png", 12, 12, 0.0f, false);
	SpriteRenderer->CreateAnimation("Silver_Col", "Bricks.png", 12, 17, 0.2f, false);
	SpriteRenderer->CreateAnimation("Gold_Idle", "Bricks.png", 18, 18, 0.0f, false);
	SpriteRenderer->CreateAnimation("Gold_Col", "Bricks.png", 18, 23, 0.2f, false);

	SpriteRenderer->SetAnimationEvent("Silver_Col", 17, [this]()
		{
			SpriteRenderer->ChangeAnimation("Silver_Idle");
		});

	SpriteRenderer->SetAnimationEvent("Gold_Col", 23, [this]()
		{
			SpriteRenderer->ChangeAnimation("Gold_Idle");
		});

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

	if (nullptr != ResultBall && true != CollisionCheck)
	{

		BallTrans.Location = { ResultBall->GetActorLocation() };
		
		//Brick ����
		if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X >(BrickTrans.Location.X - (BrickSize.X / 2)) &&
			BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					BallReflect(FVector2D::LEFT);

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect(FVector2D::UP);

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
					BallReflect(FVector2D::LEFT);

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect(FVector2D::DOWN);

					BrickDestroyCheck();
				}
			}
		}


		//Brick ������
		if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
			BallTrans.Location.Y >(BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

			if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					BallReflect(FVector2D::RIGHT);

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					BallReflect(FVector2D::UP);

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
					BallReflect(FVector2D::RIGHT);

					BrickDestroyCheck();
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					BallReflect(FVector2D::DOWN);

					BrickDestroyCheck();
				}
			}
		}
	}
}


void ABrick::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
	_Ser << static_cast<int>(BrickType);
}

void ABrick::DeSerialize(UEngineSerializer& _Ser)
{
}


void ABrick::BrickDestroyCheck()
{
	BrickHP -= 1;

	if (1 == BrickHP && EBrickType::SILVER == BrickType)
	{
		BrickProtectSound = UEngineSound::Play("BrickProtect.wav");
		BrickProtectSound.SetVolume(0.2f);
		SpriteRenderer->ChangeAnimation("Silver_Col");
		return;
	}

	if (EBrickType::GOLD == BrickType)
	{
		BrickProtectSound = UEngineSound::Play("BrickProtect.wav");
		BrickProtectSound.SetVolume(0.2f);
		SpriteRenderer->ChangeAnimation("Gold_Col");
		return;
	}

	if (0 == BrickHP)
	{
		CollisionCheck = true;
		AStage::BrickList.remove(this);
		AStage::Bricks.remove(this);
		Ball_BrickSound = UEngineSound::Play("Ball_Brick.wav");
		Ball_BrickSound.SetVolume(0.2f);

		this->Destroy();

		AItem* Ptr = GetWorld()->SpawnActor<AItem>();
		Ptr->SetActorLocation(GetActorLocation());
		Ptr->SetPlayerLife(PlayerLife);
		Ptr->SetBall(ResultBall);

		Vaus->AddPlayerScore(Score);
	}
}

void ABrick::BallReflect(FVector2D _Vector)
{
	FVector2D Dir;
	Dir = ResultBall->GetBallDir().Reflect(_Vector);

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
	SpriteRenderer->ChangeAnimation("Silver_Idle");
	Score = 50 * AStage::Stage;
	BrickHP = 2;
}

void ABrick::GoldBrick()
{
	SpriteRenderer->ChangeAnimation("Gold_Idle");
	Score = 0;
	BrickHP = -1;
}


