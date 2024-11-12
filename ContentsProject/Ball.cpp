#include "PreCompile.h"
#include "Ball.h"
#include "Player.h"
#include "PlayerLife.h"

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

ABall* ABall::Ball = nullptr;



void ABall::RunSoundPlay()
{
	//UEngineDebug::OutPutString("SoundPlay");
}

ABall::ABall()
{
	
	Ball = this;

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Ball.png");
	SpriteRenderer->SetComponentScale({ 20, 16 });
	SpriteRenderer->SetOrder(ERenderOrder::BALL);

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

void ABall::BeginPlay()
{
	Super::BeginPlay();

	APlayer* Vaus = GetWorld()->GetPawn<APlayer>();
	SetActorLocation({ Vaus->GetActorLocation().X, Vaus->GetActorLocation().Y - SpriteRenderer->GetComponentScale().Y});
	Dir.Radian(30.f);
	Dir.Normalize();
}

void ABall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	APlayer* Vaus = GetWorld()->GetPawn<APlayer>();
	CheckTime += _DeltaTime;

	AddActorLocation(Dir * _DeltaTime * Speed);

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