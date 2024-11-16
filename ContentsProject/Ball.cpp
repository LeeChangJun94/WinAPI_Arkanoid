#include "PreCompile.h"
#include "Ball.h"
#include "Player.h"
#include "PlayerLife.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>

#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

//ABall* ABall::Ball = nullptr;

void ABall::RunSoundPlay()
{
	//UEngineDebug::OutPutString("SoundPlay");
}

ABall::ABall()
{
	
	//Ball = this;

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Ball.png");
	SpriteRenderer->SetComponentScale({ 20, 16 });
	SpriteRenderer->SetOrder(ERenderOrder::BALL);

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 1, 1 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Ball);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	
	Dir.Radian(30.0f);


}

ABall::~ABall()
{
}

void ABall::BorderReflect(float _DeltaTime)
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	if (32 > GetActorLocation().X)
	{
		if (Dir.X < 0)
		{
			Dir = Dir.Reflect(FVector2D::RIGHT);
		}
	}

	if (WindowSize.X - 32 < GetActorLocation().X)
	{
		if (Dir.X > 0)
		{
			Dir = Dir.Reflect(FVector2D::LEFT);
		}
	}

	if (80 > GetActorLocation().Y)
	{
		if (Dir.Y < 0)
		{
			Dir = Dir.Reflect(FVector2D::DOWN);
		}

	}

	if (WindowSize.Y < GetActorLocation().Y)
	{
		//APlayerLife::PlayerLife->SetLifeCount(-1);
		//ReStart(_DeltaTime);
	}
}

void ABall::ReStart(float _DeltaTime)
{
	StartTime = true;
	CheckTime = 0.0f;
	CheckTime += _DeltaTime;
	if (CheckTime < 5.0f && true == StartTime)
	{
		APlayer* Vaus = GetWorld()->GetPawn<APlayer>();
		SetActorLocation({ Vaus->GetActorLocation().X + 5.0f, Vaus->GetActorLocation().Y - SpriteRenderer->GetComponentScale().Y });
		if (true == UEngineInput::GetInst().IsDown('J'))
		{
			StartTime = false;
		}
	}
}

void ABall::SetBallSpeed(float _Speed)
{
	Speed = _Speed;
}

FVector2D ABall::GetBallDir()
{
	return Dir;
}

void ABall::SetBallDir(FVector2D _Dir)
{
	Dir = _Dir;
}

void ABall::SetBallDir(float _Dir1, float _Dir2)
{
	Dir.X += _Dir1;
	Dir.Y += _Dir2;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	Vaus = GetWorld()->GetPawn<APlayer>();
	//SetActorLocation({ Vaus->GetActorLocation().X + 5.0f, Vaus->GetActorLocation().Y - SpriteRenderer->GetComponentScale().Y });
}

void ABall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	CheckTime += _DeltaTime;
	Dir.Normalize();

	if (false == BallCatch)
	{
		AddActorLocation(Dir * _DeltaTime * Speed);
	}

	BorderReflect(_DeltaTime);

	if (CheckTime < 5.0f && true == StartTime)
	{
		SetActorLocation({ Vaus->GetActorLocation().X + 5.0f, Vaus->GetActorLocation().Y - SpriteRenderer->GetComponentScale().Y});
		if (true == UEngineInput::GetInst().IsDown('J'))
		{
			StartTime = false;
		}
	}
}