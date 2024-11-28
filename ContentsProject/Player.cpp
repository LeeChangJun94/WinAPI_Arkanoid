#include "PreCompile.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Bullet.h"
#include "Item.h"
#include "PlayerLife.h"
#include "Stage.h"
#include "Stage_Boss.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
#include "ContentsEnum.h"


void APlayer::RunSoundPlay()
{
}

APlayer::APlayer()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SetActorLocation({ 336,708 });

	SpriteRenderer->CreateAnimation("Vaus_Idle", "Vaus_Idle.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Create", "Vaus_Create.png", 0, 4, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_TEnlarge", "Vaus_TEnlarge.png", 0, 4, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_RTEnlarge", "Vaus_TEnlarge.png", 4, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Enlarge", "Vaus_Enlarge.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_TLaser", "Vaus_TLaser.png", 0, 8, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_RTLaser", "Vaus_TLaser.png", 8, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Laser", "Vaus_Laser.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Destroy1", "Vaus_Destroy1.png", 0, 2, 0.2f);
	SpriteRenderer->CreateAnimation("Vaus_Destroy2", "Vaus_Destroy2.png", 0, 3, 0.2f);

	SpriteRenderer->SetAnimationEvent("Vaus_TEnlarge", 4, std::bind(&APlayer::EnlargeDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_RTEnlarge", 4, std::bind(&APlayer::IdleStart, this));
	SpriteRenderer->SetAnimationEvent("Vaus_TLaser", 8, std::bind(&APlayer::LaserDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Destroy1", 2, std::bind(&APlayer::DestroyDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Destroy2", 3, std::bind(&APlayer::VausReset, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Create", 4, std::bind(&APlayer::CreateDone, this));
	
	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 96, 24 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Vaus);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(PlayerState::Create);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Z'))
	{
		ChangeState(PlayerState::Laser);
	}

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("CurStage : " + std::to_string(AStage::Stage));

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}

	ABall* ResultBall = reinterpret_cast<ABall*>(CollisionComponent->CollisionOnce(ECollisionGroup::Ball));

	FVector2D VausSize = SpriteRenderer->GetComponentScale();
	VausTrans.Location = { GetActorLocation() };
	Ratio = (VausSize.Y / 2) / (VausSize.X / 2);
	
	if (nullptr != ResultBall)
	{
		BallTrans.Location = { ResultBall->GetActorLocation() };
		if (BallTrans.Location.X < VausTrans.Location.X && BallTrans.Location.X >(VausTrans.Location.X - (VausSize.X / 2)) &&
			BallTrans.Location.Y > (VausTrans.Location.Y - (VausSize.Y / 2)) && BallTrans.Location.Y < VausTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - VausTrans.Location.X);

			if ((Line) > (VausTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.3))
					{
						FVector2D Dir;
						Dir.Radian(-30.0f);
						ResultBall->SetBallDir(Dir);
					}
					else if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.6))
					{
						FVector2D Dir;
						Dir.Radian(-45.0f);
						ResultBall->SetBallDir(Dir);
					}
					else
					{
						FVector2D Dir;
						Dir.Radian(-60.0f);
						ResultBall->SetBallDir(Dir);
					}

					if (true == CatchEffect)
					{
						std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
						std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
						for (; BalliterStart != BalliterEnd; ++BalliterStart)
						{
							(*BalliterStart)->SetBallCatch(true);
							(*BalliterStart)->Distance = GetActorLocation().X - (*BalliterStart)->GetActorLocation().X;
						}
					}
				}
			}
		}

		if (BallTrans.Location.X < VausTrans.Location.X && BallTrans.Location.X >(VausTrans.Location.X - (VausSize.X / 2)) &&
			BallTrans.Location.Y < (VausTrans.Location.Y + (VausSize.Y / 2)) && BallTrans.Location.Y > VausTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - VausTrans.Location.X);

			if ((Line) < (VausTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					ResultBall->SetBallDir(Dir);
				}
			}
		}



		if (BallTrans.Location.X > VausTrans.Location.X && BallTrans.Location.X < (VausTrans.Location.X + (VausSize.X / 2)) &&
			BallTrans.Location.Y >(VausTrans.Location.Y - (VausSize.Y / 2)) && BallTrans.Location.Y < VausTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - VausTrans.Location.X);

			if ((Line) > (VausTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.3))
					{
						FVector2D Dir;
						Dir.Radian(30.0f);

						ResultBall->SetBallDir(Dir);
					}
					else if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.6))
					{
						FVector2D Dir;
						Dir.Radian(45.0f);

						ResultBall->SetBallDir(Dir);
					}
					else
					{
						FVector2D Dir;
						Dir.Radian(60.0f);

						ResultBall->SetBallDir(Dir);
					}

					if (true == CatchEffect)
					{
						std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
						std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
						for (; BalliterStart != BalliterEnd; ++BalliterStart)
						{
							(*BalliterStart)->SetBallCatch(true);
							(*BalliterStart)->Distance = GetActorLocation().X - (*BalliterStart)->GetActorLocation().X;
						}
					}
				}
			}
		}

		if (BallTrans.Location.X > VausTrans.Location.X && BallTrans.Location.X < (VausTrans.Location.X + (VausSize.X / 2)) &&
			BallTrans.Location.Y < (VausTrans.Location.Y + (VausSize.Y / 2)) && BallTrans.Location.Y > VausTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - VausTrans.Location.X);

			if ((Line) < (VausTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					Ball_VausSound = UEngineSound::Play("Ball_Vaus.wav");
					Ball_VausSound.SetVolume(0.2f);
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					ResultBall->SetBallDir(Dir);
				}
			}
		}
	}

	switch (CurPlayerState)
	{
	case PlayerState::Idle:
		Idle(_DeltaTime);
		break;
	case PlayerState::Laser:
		Laser(_DeltaTime);
		break;
	case PlayerState::Enlarge:
		Enlarge(_DeltaTime);
		break;
	default:
		break;
	}

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	if (true == UEngineInput::GetInst().IsPress('D') && 0 != PlayerLife->BallList.size())
	{
		if (WindowSize.X - 24 > GetActorLocation().X + VausSize.Half().X)
		{
			AddActorLocation(FVector2D::RIGHT * _DeltaTime * (Speed * 2));
		}
	}
	if (true == UEngineInput::GetInst().IsPress('A') && 0 != PlayerLife->BallList.size())
	{
		if (24 < GetActorLocation().X - VausSize.Half().X)
		{
			AddActorLocation(FVector2D::LEFT * _DeltaTime * (Speed * 2));
		}
	}
	
	std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
	std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();

	if (BalliterEnd != BalliterStart)
	{
		if (true == (*BalliterStart)->GetBallCatch())
		{
			if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
			{
				for (; BalliterStart != BalliterEnd; ++BalliterStart)
				{
					(*BalliterStart)->SetBallCatch(false);
				}
			}

			for (; BalliterStart != BalliterEnd; ++BalliterStart)
			{
				(*BalliterStart)->SetActorLocation({ GetActorLocation().X - (*BalliterStart)->Distance, (*BalliterStart)->GetActorLocation().Y });
			}
		}
	}
}

void APlayer::ChangeState(PlayerState _CurPlayerState)
{
	switch (_CurPlayerState)
	{
	case PlayerState::Create:
		VausReset();
		break;
	case PlayerState::Idle:
		IdleStart();
		break;
	case PlayerState::Laser:
		LaserStart();
		break;
	case PlayerState::Enlarge:
		EnlargeStart();
		break;
	case PlayerState::Destroy:
		DestroyStart();
		break;
	default:
		break;
	}

	CurPlayerState = _CurPlayerState;
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}

void APlayer::IdleStart()
{
	SpriteRenderer->ChangeAnimation("Vaus_Idle");
}

void APlayer::Idle(float _DeltaTime)
{
}

void APlayer::LaserStart()
{
	SpriteRenderer->SetComponentScale({ 96, 24 });
	CollisionComponent->SetComponentScale({ 96, 24 });
	SpriteRenderer->ChangeAnimation("Vaus_TLaser");
}

void APlayer::LaserDone()
{
	SpriteRenderer->ChangeAnimation("Vaus_Laser");

}

void APlayer::Laser(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
	{
		LaserSound = UEngineSound::Play("Item_Laser.wav");
		LaserSound.SetVolume(0.2f);
		if (2 >= BulletPtr.size())
		{
 			ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
			BulletPtr.push_back(Ptr);
		}
	}
}

void APlayer::EnlargeStart()
{
	EnlargeSound = UEngineSound::Play("Item_Enlarge.wav");
	EnlargeSound.SetVolume(0.2f);
	SpriteRenderer->SetComponentScale({ 144, 24 });
	CollisionComponent->SetComponentScale({ 144, 24 });
	SpriteRenderer->ChangeAnimation("Vaus_TEnlarge");
}

void APlayer::EnlargeDone()
{
	SpriteRenderer->ChangeAnimation("Vaus_Enlarge");
}

void APlayer::DestroyStart()
{
	VausDeadSound = UEngineSound::Play("VausDead.wav");
	VausDeadSound.SetVolume(0.2f);
	SpriteRenderer->ChangeAnimation("Vaus_Destroy1");
	CollisionComponent->SetActive(false);
}

void APlayer::DestroyDone()
{
	SpriteRenderer->SetComponentScale({ 144, 72 });
	SpriteRenderer->ChangeAnimation("Vaus_Destroy2");
}

void APlayer::VausReset()
{
	SetActorLocation({ 336,708 });
	SpriteRenderer->SetComponentScale({ 96, 24 });
	SpriteRenderer->ChangeAnimation("Vaus_Create");
	StartSwitch = true;
	CatchEffect = false;
	SlowEffect = false;
	AStage::StageCountTime = 0.0f;
	AStage::StageStartSound = true;
	AStage_Boss::BossCountTime = 0.0f;
	AStage_Boss::BossStartSound = true;
	SetActive(false);
}

void APlayer::CreateDone()
{
	ChangeState(PlayerState::Idle);
}

void APlayer::Enlarge(float _DeltaTime)
{

}

void APlayer::CatchStart()
{
}

void APlayer::Catch(float _DeltaTime)
{
}
