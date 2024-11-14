#include "PreCompile.h"
#include "PlayerLife.h"
#include "Ball.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineWindow.h>
#include "ContentsEnum.h"


APlayerLife::APlayerLife()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 240, 24 });
	SpriteRenderer->SetOrder(ERenderOrder::UI);
	SpriteRenderer->SetComponentLocation({ 144 , 756});

	SpriteRenderer->CreateAnimation("ZeroLife", "PlayerLife_0.png", 0, 0);
	SpriteRenderer->CreateAnimation("OneLife", "PlayerLife_1.png", 0, 0);
	SpriteRenderer->CreateAnimation("TwoLife", "PlayerLife_2.png", 0, 0);
	SpriteRenderer->CreateAnimation("ThreeLife", "PlayerLife_3.png", 0, 0);
	SpriteRenderer->CreateAnimation("FourLife", "PlayerLife_4.png", 0, 0);
	SpriteRenderer->CreateAnimation("FiveLife", "PlayerLife_5.png", 0, 0);

	SpriteRenderer->ChangeAnimation("TwoLife");
}

APlayerLife::~APlayerLife()
{
}

void APlayerLife::BeginPlay()
{
	Super::BeginPlay();

}

bool APlayerLife::DeathCheck()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	float BallY = Ball->GetActorLocation().Y;
	if (WindowSize.Y > BallY)
	{
		return false;
	}
	LifeCount -= 1;
	Ball->ReStart(0.0f);
	return true;
}

void APlayerLife::LifeCheck()
{
	if (0 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("ZeroLife");
	}
	else if (1 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("OneLife");
	}
	else if (2 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("TwoLife");
	}
	else if (3 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("ThreeLife");
	}
	else if (4 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("FourLife");
	}
	else if (5 == LifeCount)
	{
		SpriteRenderer->ChangeAnimation("FiveLife");
	}
}

void APlayerLife::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == DeathCheck())
	{
		LifeCheck();
	}
}


