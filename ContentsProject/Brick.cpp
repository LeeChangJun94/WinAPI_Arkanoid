#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Brick.h"
#include "Player.h"




ABrick::ABrick()
{
	SetActorLocation({ 600, 300});
	SetActorScale({ 800, 300 });
} 

ABrick::~ABrick()
{
}


void ABrick::BeginPlay()
{

}


void ABrick::Tick(float _DeltaTime)
{
	BallTrans.Location = { APlayer::Ball->GetActorLocation().iX(), APlayer::Ball->GetActorLocation().iY() };
	BallTrans.Scale = { APlayer::Ball->GetActorScale().iX(), APlayer::Ball->GetActorScale().iY() };
	
	//BallX = APlayer::Ball->GetActorLocation().iX();
	//BallY = APlayer::Ball->GetActorLocation().iY();
	//BallScaleX = APlayer::Ball->GetActorScale().iX();
	//BallScaleY = APlayer::Ball->GetActorScale().iY();

	BrickTrans.Location = { GetActorLocation().iX(), GetActorLocation().iY() };
	BrickTrans.Scale = { GetActorScale().iX(), GetActorScale().iY() };

	//BrickX = GetActorLocation().iX();
	//BrickY = GetActorLocation().iY();
	//BrickScaleX = GetActorScale().iX();
	//BrickScaleY = GetActorScale().iY();

	ratio = (BrickTrans.Scale.Y / 2) / (BrickTrans.Scale.X / 2);
	//line = ratio * (BallTrans.Location.X / 2) - (BrickTrans.Scale.Y / 2);
	


	//Brick 왼쪽
	if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X > (BrickTrans.Location.X - (BrickTrans.Scale.X / 2)) &&
		BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickTrans.Scale.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
	{
		line = (-ratio) * (BallTrans.Location.X - BrickTrans.Location.X);
		
		if ((line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (APlayer::Ball->Dir.X > 0)
			{
				APlayer::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (APlayer::Ball->Dir.Y > 0)
			{
				APlayer::Ball->Dir.Y *= -1;
			}
			
		}
	}

	if (BallTrans.Location.X < BrickTrans.Location.X && BallTrans.Location.X > (BrickTrans.Location.X - (BrickTrans.Scale.X / 2)) &&
		BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickTrans.Scale.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
	{
		line = ratio * (BallTrans.Location.X - BrickTrans.Location.X);

		if ((line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Left");
			if (APlayer::Ball->Dir.X > 0)
			{
				APlayer::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (APlayer::Ball->Dir.Y < 0)
			{
				APlayer::Ball->Dir.Y *= -1;
			}
		}
	}


	//Brick 오른쪽
	if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickTrans.Scale.X / 2)) &&
		BallTrans.Location.Y > (BrickTrans.Location.Y - (BrickTrans.Scale.Y / 2)) && BallTrans.Location.Y < BrickTrans.Location.Y)
	{
		line = ratio * (BallTrans.Location.X - BrickTrans.Location.X);

		if ((line) > (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Right");
			if (APlayer::Ball->Dir.X < 0)
			{
				APlayer::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Top");
			if (APlayer::Ball->Dir.Y > 0)
			{
				APlayer::Ball->Dir.Y *= -1;
			}
		}
	}

	if (BallTrans.Location.X > BrickTrans.Location.X && BallTrans.Location.X < (BrickTrans.Location.X + (BrickTrans.Scale.X / 2)) &&
		BallTrans.Location.Y < (BrickTrans.Location.Y + (BrickTrans.Scale.Y / 2)) && BallTrans.Location.Y > BrickTrans.Location.Y)
	{
		line = (-ratio) * (BallTrans.Location.X - BrickTrans.Location.X);

		if ((line) < (BrickTrans.Location.Y - BallTrans.Location.Y))
		{
			UEngineDebug::OutPutString("Right");
			if (APlayer::Ball->Dir.X < 0)
			{
				APlayer::Ball->Dir.X *= -1;
			}
		}
		else
		{
			UEngineDebug::OutPutString("Bottom");
			if (APlayer::Ball->Dir.Y < 0)
			{
				APlayer::Ball->Dir.Y *= -1;
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

