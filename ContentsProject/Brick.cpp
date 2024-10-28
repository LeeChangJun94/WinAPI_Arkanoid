#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include "Brick.h"
#include "Player.h"




ABrick::ABrick()
{
	SetActorLocation({ 700, 300});
	SetActorScale({ 1000, 300 });
}

ABrick::~ABrick()
{
}


void ABrick::BeginPlay()
{
}


void ABrick::Tick(float _DeltaTime)
{
	BallX = APlayer::Ball->GetActorLocation().iX();
	BallY = APlayer::Ball->GetActorLocation().iY();
	BallScaleX = APlayer::Ball->GetActorScale().iX();
	BallScaleY = APlayer::Ball->GetActorScale().iY();

	BrickX = GetActorLocation().iX();
	BrickY = GetActorLocation().iY();
	BrickScaleX = GetActorScale().iX();
	BrickScaleY = GetActorScale().iY();

	

	//왼쪽
	if ((BrickX - (BrickScaleX / 2) - (BallScaleX / 2) == BallX))
	{
		if (BallY > GetActorLocation().iY() - (BrickScaleY / 2  + BallScaleY / 2) && BallY < GetActorLocation().iY() + (BrickScaleY / 2 + BallScaleY / 2))
		{
			int a = 10;
		}
	}

	//오른쪽
	if ((BrickX + (BrickScaleX / 2) + (BallScaleX / 2) == BallX))
	{
		if (BallY > GetActorLocation().iY() - (BrickScaleY / 2 + BallScaleY / 2) && BallY < GetActorLocation().iY() + (BrickScaleY / 2 + BallScaleY / 2))
		{
			int a = 10;
		}
	}

	//위쪽
	if ((BrickY - (BrickScaleY / 2) - (BallScaleY / 2) == BallY))
	{
		if (BallX > GetActorLocation().iX() - (BrickScaleX / 2 + BallScaleX / 2) && BallX < GetActorLocation().iX() + (BrickScaleX / 2 + BallScaleX / 2))
		{
			int a = 10;
		}
	}

	//아래쪽
	if ((BrickY + (BrickScaleY / 2) + (BallScaleY / 2) == BallY))
	{
		if (BallX > GetActorLocation().iX() - (BrickScaleX / 2 + BallScaleX / 2) && BallX < GetActorLocation().iX() + (BrickScaleX / 2 + BallScaleX / 2))
		{
			int a = 10;
		}
	}

}

