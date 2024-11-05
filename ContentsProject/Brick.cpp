#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Item.h"

#include <EngineCore/ImageManager.h>


ABrick::ABrick()
{
	//SetActorLocation({ 600, 300});
	//SetActorScale({ 32, 16 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bricks1.png");
	SpriteRenderer->SetComponentScale({ 48, 24 });
	//SetActorScale(SpriteRenderer->GetComponentScale());
} 

ABrick::~ABrick()
{
}


void ABrick::BeginPlay()
{

}


void ABrick::Tick(float _DeltaTime)
{
	BallTrans.Location = { ABall::Ball->GetActorLocation().iX(), ABall::Ball->GetActorLocation().iY() };
	//BallTrans.Scale = { ABall::Ball->GetActorScale().iX(), ABall::Ball->GetActorScale().iY() };
	
	//BallX = APlayer::Ball->GetActorLocation().iX();
	//BallY = APlayer::Ball->GetActorLocation().iY();
	//BallScaleX = APlayer::Ball->GetActorScale().iX();
	//BallScaleY = APlayer::Ball->GetActorScale().iY();

	//FVector2D BallSize = ABall::Ball->GetBallScale();

	BrickTrans.Location = { GetActorLocation().iX(), GetActorLocation().iY() };
	//BrickTrans.Scale= { GetActorScale().iX(), GetActorScale().iY() };*/

	FVector2D BrickSize = SpriteRenderer->GetComponentScale();
	//BrickX = GetActorLocation().iX();
	//BrickY = GetActorLocation().iY();
	//BrickScaleX = GetActorScale().iX();
	//BrickScaleY = GetActorScale().iY();

	Ratio = (BrickSize.Y / 2) / (BrickSize.X / 2);
	//line = ratio * (BallTrans.Location.X / 2) - (BrickSize.Y / 2);
	


	//Brick 왼쪽
	if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X > (BrickTrans.Location.X - (BrickSize.X / 2)) &&
		BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
	{
		Line = (-Ratio) * (BallTrans.Location.X - BrickTrans.Location.X);
		
		if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (ABall::Ball->Dir.X > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::LEFT);

				ABall::Ball->Dir = Dir;
				
				this->Destroy();

				APlayer::Vaus->AddPlayerScore(1000);
				//APlayer::Ball->Dir.X *= -1;

			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (ABall::Ball->Dir.Y > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::UP);

				ABall::Ball->Dir = Dir;

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//ABall::Ball->Dir.Y *= -1;

			}
			
		}
	}

	if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X > (BrickTrans.Location.X - (BrickSize.X / 2)) &&
		BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickSize.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
	{
		Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

		if ((Line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (ABall::Ball->Dir.X > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::LEFT);

				ABall::Ball->Dir = Dir;

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//ABall::Ball->Dir.X *= -1;

			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (ABall::Ball->Dir.Y < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::DOWN);
				
				ABall::Ball->Dir = Dir;

				AItem* Ptr = GetWorld()->SpawnActor<AItem>();
				Ptr->SetActorLocation(GetActorLocation());

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//Ptr->USpriteRenderer::ChangeAnimation("Player");
				//APlayer::Ball->Dir.Y *= -1;
			}
		}
	}


	//Brick 오른쪽
	if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickSize.X / 2)) &&
		BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickSize.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
	{
		Line = Ratio * (BallTrans.Location.X - BrickTrans.Location.X);

		if ((Line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Right");
			if (ABall::Ball->Dir.X < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::RIGHT);

				ABall::Ball->Dir = Dir;

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//ABall::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (ABall::Ball->Dir.Y > 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::UP);

				ABall::Ball->Dir = Dir;

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
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
			if (ABall::Ball->Dir.X < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::RIGHT);

				ABall::Ball->Dir = Dir;

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//ABall::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (ABall::Ball->Dir.Y < 0)
			{
				FVector2D Dir;
				Dir = ABall::Ball->Dir.Reflect(FVector2D::DOWN);
				
				ABall::Ball->Dir = Dir;

				AItem* Ptr = GetWorld()->SpawnActor<AItem>();
				Ptr->SetActorLocation(GetActorLocation());

				this->Destroy();
				APlayer::Vaus->AddPlayerScore(1000);
				//Ptr->USpriteRenderer::SpriteRenderer2
				//Ptr->USpriteRenderer::ChangeAnimation("Player");

				//ABall::Ball->Dir.Y *= -1;
			}
		}
	}


	//왼쪽
	/*if ((BrickX - (BrickScaleX / 2) - (BallScaleX / 2) == BallX))
	{
		if (BallY > GetActorLocation().iY() - (BrickScaleY / 2  + BallScaleY / 2) && BallY < GetActorLocation().iY() + (BrickScaleY / 2 + BallScaleY / 2))
		{
			UEngineDebug::OutPutString("left");
		}
	}*/

	//오른쪽
	//if ((BrickX + (BrickScaleX / 2) + (BallScaleX / 2) == BallX))
	//{
	//	if (BallY > GetActorLocation().iY() - (BrickScaleY / 2 + BallScaleY / 2) && BallY < GetActorLocation().iY() + (BrickScaleY / 2 + BallScaleY / 2))
	//	{
	//		UEngineDebug::OutPutString("right");
	//	}
	//}
	//
	////위쪽
	//if ((BrickY - (BrickScaleY / 2) - (BallScaleY / 2) == BallY))
	//{
	//	if (BallX > GetActorLocation().iX() - (BrickScaleX / 2 + BallScaleX / 2) && BallX < GetActorLocation().iX() + (BrickScaleX / 2 + BallScaleX / 2))
	//	{
	//		UEngineDebug::OutPutString("up");
	//	}
	//}
	//
	////아래쪽
	//if ((BrickY + (BrickScaleY / 2) + (BallScaleY / 2) == BallY))
	//{
	//	if (BallX > GetActorLocation().iX() - (BrickScaleX / 2 + BallScaleX / 2) && BallX < GetActorLocation().iX() + (BrickScaleX / 2 + BallScaleX / 2))
	//	{
	//		UEngineDebug::OutPutString("down");
	//	}
	//}

}

