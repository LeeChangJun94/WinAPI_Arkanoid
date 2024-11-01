#include "PreCompile.h"
#include "Ball.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>

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
	SetActorLocation({ APlayer::Vaus->GetActorLocation().X + GetActorScale().X , APlayer::Vaus->GetActorLocation().Y + GetActorScale().Y});
}

ABall::~ABall()
{
}

void ABall::BeginPlay()
{
	Super::BeginPlay();

	Dir.Radian(30.f);
	Dir.Normalize();
}

void ABall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(Dir * _DeltaTime * Speed);

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

	if (32 > GetActorLocation().Y)
	{
		if (Dir.Y < 0)
		{
			Dir = Dir.Reflect(FVector2D::DOWN);
		}

	}

	if (WindowSize.Y < GetActorLocation().Y)
	{
		if (Dir.Y > 0)
		{
			Dir = Dir.Reflect(FVector2D::UP);
		}
	}
}