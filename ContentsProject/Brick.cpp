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

//FVector2D ABrick::ReflectionVector[static_cast<int>(EReflectionDir::MAX)] = {
//	{1, 0},	// LEFT,
//	{-1, 0},	// RIGHT,
//	{0, 1},					// UP,
//	{0, -1},					// DOWN,
//};

ABrick::ABrick()
{
	//SetActorLocation({ 600, 300});
	//SetActorScale({ 32, 16 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bricks1.png");
	SpriteRenderer->SetComponentScale({ 48, 24 });
	//SetActorScale(SpriteRenderer->GetComponentScale());

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
}

//bool ABrick::RectCheck()
//{
//	// 필요한 값들을 다 모아서 정렬한다.
//	FTransform BallTransform = ABall::Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	FVector2D LeftTop = BrickTransform.CenterLeftTop();
//	FVector2D RatioPos = BallTransform.Location - LeftTop;
//
//	// 계산값들을 미리 계산해 놓는다.
//	RatioPos.X /= 48;
//	RatioPos.Y /= 24;
//
//	// 절대 아닌 사항리턴하기 시작한다.
//
//	if (0.0f > RatioPos.X)
//	{
//		return false;
//	}
//
//	if (0.0f > RatioPos.Y)
//	{
//		return false;
//	}
//
//	if (1.0f < RatioPos.X)
//	{
//		return false;
//	}
//
//	if (1.0f < RatioPos.Y)
//	{
//		return false;
//	}
//
//	return true;
//}

//bool ABrick::RectCheck()
//{
//	FTransform BallTransform = Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	if (BallTransform.Location.X < BrickTransform.Location.X && BallTransform.Location.X > (BrickTransform.Location.X - (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y > (BrickTransform.Location.Y - (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y < BrickTransform.Location.Y)
//	{
//		LeftTop = true;
//		return LeftTop;
//	}
//	
//	if (BallTransform.Location.X < BrickTransform.Location.X && BallTransform.Location.X >(BrickTransform.Location.X - (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y < (BrickTransform.Location.Y + (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y > BrickTransform.Location.Y)
//	{
//		LeftBottom = true;
//		return LeftBottom;
//	}
//
//	if (BallTransform.Location.X > BrickTransform.Location.X && BallTransform.Location.X < (BrickTransform.Location.X + (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y > (BrickTransform.Location.Y - (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y < BrickTransform.Location.Y)
//	{
//		RightTop = true;
//		return RightTop;
//	}
//
//	if (BallTransform.Location.X > BrickTransform.Location.X && BallTransform.Location.X < (BrickTransform.Location.X + (BrickTransform.Scale.X / 2)) &&
//		BallTransform.Location.Y < (BrickTransform.Location.Y + (BrickTransform.Scale.Y / 2)) && BallTransform.Location.Y > BrickTransform.Location.Y)
//	{
//		RightBottom = true;
//		return RightBottom;
//	}
//
//	LeftTop = false;
//	LeftBottom = false;
//	RightTop = false;
//	RightBottom = false;
//
//	return false;
//}

//EReflectionDir ABrick::ReflectionDirCheck()
//{
//	FTransform BallTransform = ABall::Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	FVector2D LeftTop = BrickTransform.CenterLeftTop();
//	FVector2D LRRatioPos = BallTransform.Location - LeftTop;
//
//	// 계산값들을 미리 계산해 놓는다.
//	LRRatioPos.X /= 48;
//	LRRatioPos.Y /= 24;
//
//	// 에러 값으로 세팅해 놓는다.
//	// 만약에 내가 아래쪽 코드를 잘못 짰다면
//	EReflectionDir Dir = EReflectionDir::MAX;
//
//	// 오른쪽 삼각형
//	if (LRRatioPos.X > LRRatioPos.Y)
//	{
//		Dir = EReflectionDir::RIGHT;
//	}
//	else 
//	{
//		Dir = EReflectionDir::LEFT;
//	}
//
//	FVector2D BTRatioPos = LRRatioPos;
//	BTRatioPos.X = 1.0f - BTRatioPos.X;
//	BTRatioPos.Y = 1.0f - BTRatioPos.Y;
//
//	if (BTRatioPos.X < BTRatioPos.Y)
//	{
//		if (Dir == EReflectionDir::RIGHT)
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//	else 
//	{
//		if (Dir == EReflectionDir::LEFT)
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	return Dir;
//}

//EReflectionDir ABrick::ReflectionDirCheck()
//{
//	FTransform BallTransform = //Ball->GetTransform();
//	FTransform BrickTransform = SpriteRenderer->GetActorTransform();
//
//	float Ratio = (BrickTransform.Scale.Y / 2) / (BrickTransform.Scale.X / 2);
//
//	float LeftLine = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);
//	float RightLine = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);
//
//	EReflectionDir Dir = EReflectionDir::MAX;
//
//	if (true == LeftTop)
//	{
//		if (LeftLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::LEFT;
//		}
//		else
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//	
//	if (true == LeftBottom)
//	{
//		if (RightLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::LEFT;
//		}
//		else
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	if (true == RightTop)
//	{
//		if (RightLine > (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::RIGHT;
//		}
//		else
//		{
//			Dir = EReflectionDir::UP;
//		}
//	}
//
//	if (true == RightBottom)
//	{
//		if (LeftLine < (BrickTrans.Location.Y - BallTrans.Location.Y))
//		{
//			Dir = EReflectionDir::RIGHT;
//		}
//		else
//		{
//			Dir = EReflectionDir::DOWN;
//		}
//	}
//
//	return Dir;
//}

void ABrick::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == RectCheck())
	//{
	//	EReflectionDir Dir = ReflectionDirCheck();
	//
	//	FVector2D DirVector = ReflectionVector[static_cast<int>(Dir)];
	//
	//	DirVector = ABall::Ball->Dir.Reflect(DirVector);
	//
	//	ABall::Ball->Dir = DirVector;
	//
	//	this->Destroy();
	//
	//}
	//
	//return;

	//BallTrans.Location = { Ball->GetActorLocation().X, Ball->GetActorLocation().Y };
	BrickTrans.Location = { GetActorLocation() };

	FVector2D BrickSize = SpriteRenderer->GetComponentScale();

	Ratio = (BrickSize.Y / 2) / (BrickSize.X / 2);
	//line = ratio * (BallTrans.Location.X / 2) - (BrickSize.Y / 2);


	AActor* ResultBall = CollisionComponent->CollisionOnce(ECollisionGroup::Ball);

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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					//ABall::Ball->BallReflection(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);

					this->Destroy();

					Vaus->AddPlayerScore(80);

					//APlayer::Ball->Dir.X *= -1;

				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::UP);

					ResultBall->SetBallDir(Dir);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//ABall::Ball->Dir.Y *= -1;

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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//ABall::Ball->Dir.X *= -1;

				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					ResultBall->SetBallDir(Dir);

					AItem* Ptr = GetWorld()->SpawnActor<AItem>();
					Ptr->SetActorLocation(GetActorLocation());
					Ptr->SetPlayerLife(PlayerLife);
					Ptr->SetBall(ResultBall);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//Ptr->USpriteRenderer::ChangeAnimation("Player");
					//APlayer::Ball->Dir.Y *= -1;
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//ABall::Ball->Dir.X *= -1;
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::UP);

					ResultBall->SetBallDir(Dir);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//ABall::Ball->Dir.Y *= -1;
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);

					this->Destroy();
					Vaus->AddPlayerScore(80);
					//ABall::Ball->Dir.X *= -1;
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					ResultBall->SetBallDir(Dir);

					AItem* Ptr = GetWorld()->SpawnActor<AItem>();
					Ptr->SetActorLocation(GetActorLocation());
					Ptr->SetPlayerLife(PlayerLife);
					Ptr->SetBall(ResultBall);


					this->Destroy();
					Vaus->AddPlayerScore(80);
					//Ptr->USpriteRenderer::SpriteRenderer2
					//Ptr->USpriteRenderer::ChangeAnimation("Player");

					//ABall::Ball->Dir.Y *= -1;
				}
			}
		}
	}

}

