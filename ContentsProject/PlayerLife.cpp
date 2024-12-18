#include "PreCompile.h"
#include "Player.h"
#include "PlayerLife.h"
#include "DeathLine.h"
#include "Ball.h"
#include "Boss.h"
#include "GameOver.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

int APlayerLife::LifeCount = 2;

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
	Vaus = GetWorld()->GetPawn<APlayer>();
}

bool APlayerLife::DeathCheck()
{
	ABall* BallResult = reinterpret_cast<ABall*>(DeathLine->GetCollisionComponent()->CollisionOnce(ECollisionGroup::Ball));

	if (nullptr != BallResult)
	{
		BallList.remove(BallResult);
		BallResult->Destroy();
		return true;
	}

	return false;
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

	UEngineDebug::CoreOutPutString("PlayerLife : " + std::to_string(LifeCount));
	UEngineDebug::CoreOutPutString("BallListCount : " + std::to_string(BallList.size()));

	if (true == DeathCheck() || true == VausDestroy)
	{
		if (true == VausDestroy)
		{
			Boss->SetCountTime(-1.0f);
		}
		VausDestroy = false;
		if (0 == BallList.size())
		{
			Vaus->ChangeState(PlayerState::Destroy);
			
			if (0 <= LifeCount)
			{
				LifeCount -= 1;
			}
			if (-1 == LifeCount)
			{
				TimeEventer.PushEvent(1.4f, [this]()
					{
						UEngineAPICore::GetCore()->ResetLevel<AGameOver, AActor>("GameOver");
						UEngineAPICore::GetCore()->OpenLevel("GameOver");
						LifeCount = 2;
					});
			}
		}
	}
	LifeCheck();
}


