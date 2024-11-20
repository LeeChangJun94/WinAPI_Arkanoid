#include "PreCompile.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Bullet.h"
#include "Item.h"
#include "PlayerLife.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
#include "ContentsEnum.h"

//APlayer* APlayer::Vaus = nullptr;

void APlayer::RunSoundPlay()
{
	//UEngineDebug::OutPutString("SoundPlay");
}

APlayer::APlayer()
{
	//Vaus = this;
	
	//SetActorLocation({300, 700});

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("Vaus_Idle.png");
	//SpriteRenderer->SetComponentScale({ 96, 24 });
	SetActorLocation({ 336,700 });
	//SetActorScale(SpriteRenderer->GetComponentScale());

	SpriteRenderer->CreateAnimation("Vaus_Idle", "Vaus_Idle.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Create", "Vaus_Create.png", 0, 4, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_TEnlarge", "Vaus_TEnlarge.png", 0, 4, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_RTEnlarge", "Vaus_TEnlarge.png", 4, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Enlarge", "Vaus_Enlarge.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_TLaser", "Vaus_TLaser.png", 0, 8, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_RTLaser", "Vaus_TLaser.png", 8, 0, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Laser", "Vaus_Laser.png", 0, 5, 0.1f);
	//SpriteRenderer->CreateAnimation("Vaus_Lasers", "Vaus_Enlarge.png", 0, 5, 0.1f);
	//SpriteRenderer->CreateAnimation("Vaus_Lasers", "Vaus_Enlarge.png", 0, 5, 0.1f);
	SpriteRenderer->CreateAnimation("Vaus_Destroy1", "Vaus_Destroy1.png", 0, 2, 0.2f);
	SpriteRenderer->CreateAnimation("Vaus_Destroy2", "Vaus_Destroy2.png", 0, 3, 0.2f);
	//IdleStart();

	SpriteRenderer->SetAnimationEvent("Vaus_TEnlarge", 4, std::bind(&APlayer::EnlargeDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_RTEnlarge", 4, std::bind(&APlayer::IdleStart, this));
	SpriteRenderer->SetAnimationEvent("Vaus_TLaser", 8, std::bind(&APlayer::LaserDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Destroy1", 2, std::bind(&APlayer::DestroyDone, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Destroy2", 3, std::bind(&APlayer::VausReset, this));
	SpriteRenderer->SetAnimationEvent("Vaus_Create", 4, std::bind(&APlayer::CreateDone, this));
	//SpriteRenderer->SetAnimationEvent("Vaus_TLaser", 8, std::bind(&APlayer::LaserDone, this));
	
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

	//PlayerLifeActor->SetPlayerLife(this);

	ChangeState(PlayerState::Create);
	//Dir.Radian(30.f);
	//Dir.Normalize();


	// 직접 카메라 피봇을 설정해줘야 한다.
	//FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}



void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Z'))
	{
		//ChangeState(PlayerState::Enlarge);
		//DestroyStart();
		ChangeState(PlayerState::Laser);
	}

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	//UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());
	//UEngineDebug::CoreOutPutString("PlayerLife : " + std::to_string(PlayerLife->GetLifeCount()));

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
		//UEngineDebug::SwitchIsDebug();
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);

					//APlayer::Ball->Dir.X *= -1;
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.2))
					{
						FVector2D Dir;
						Dir.Radian(-30.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}
					else if (BallTrans.Location.X > VausTrans.Location.X - ((VausSize.X / 2) * 0.6))
					{
						FVector2D Dir;
						Dir.Radian(-45.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}
					else
					{
						FVector2D Dir;
						Dir.Radian(-60.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}

					if (true == CatchEffect)
					{
						std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
						std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
						for (; BalliterStart != BalliterEnd; ++BalliterStart)
						{
							(*BalliterStart)->BallCatch = true;
							(*BalliterStart)->Distance = GetActorLocation().X - (*BalliterStart)->GetActorLocation().X;
						}
						//Result->SetActorLocation({ Vaus->GetActorLocation().X, Vaus->GetActorLocation().Y });

					}

					//ABall::Ball->Dir.Y *= -1;
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					ResultBall->SetBallDir(Dir);

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

					//APlayer::Ball->Dir.Y *= -1;
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);

					//ABall::Ball->Dir.X *= -1;
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.2))
					{
						FVector2D Dir;
						Dir.Radian(30.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}
					else if (BallTrans.Location.X < VausTrans.Location.X + ((VausSize.X / 2) * 0.6))
					{
						FVector2D Dir;
						Dir.Radian(45.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}
					else
					{
						FVector2D Dir;
						Dir.Radian(60.0f);

						ResultBall->SetBallDir(Dir);
						//ChangeState(PlayerState::Laser);
					}

					if (true == CatchEffect)
					{
						std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
						std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
						for (; BalliterStart != BalliterEnd; ++BalliterStart)
						{
							(*BalliterStart)->BallCatch = true;
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
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					ResultBall->SetBallDir(Dir);

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

					//ABall::Ball->Dir.Y *= -1;
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

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		if (WindowSize.X - 24 > GetActorLocation().X + VausSize.Half().X)
		{
			AddActorLocation(FVector2D::RIGHT * _DeltaTime * (Speed * 2));
		}
	}
	if (true == UEngineInput::GetInst().IsPress('A'))
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
		if (true == (*BalliterStart)->BallCatch)
		{
			if (true == UEngineInput::GetInst().IsDown('J'))
			{
				for (; BalliterStart != BalliterEnd; ++BalliterStart)
				{
					(*BalliterStart)->BallCatch = false;
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
		if (2 >= BulletPtr.size())
		{
 			ABullet* Ptr = GetWorld()->SpawnActor<ABullet>();
			//Ptr->SetActorLocation(GetActorLocation());
			BulletPtr.push_back(Ptr);
		}
	}
}

void APlayer::EnlargeStart()
{
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
	SpriteRenderer->ChangeAnimation("Vaus_Destroy1");

}

void APlayer::DestroyDone()
{
	SpriteRenderer->SetComponentScale({ 144, 72 });
	SpriteRenderer->ChangeAnimation("Vaus_Destroy2");
}

void APlayer::VausReset()
{
	SetActorLocation({ 336,700 });
	SpriteRenderer->SetComponentScale({ 96, 24 });
	SpriteRenderer->ChangeAnimation("Vaus_Create");
	StartSwitch = true;
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
