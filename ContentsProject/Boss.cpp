#include "PreCompile.h"
#include "Boss.h"
#include "Ball.h"
#include "BossBullet.h"
#include <EngineBase/TimeEvent.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include <EngineBase/EngineMath.h>
#include "ContentsEnum.h"

ABoss::ABoss()
{
	SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetSprite("Boss.png");
	SpriteRenderer1->SetComponentScale({ 192, 288 });
	SpriteRenderer1->SetOrder(ERenderOrder::ENEMIES);
	SpriteRenderer1->CreateAnimation("Boss_Normal", "Boss.png", 0, 3, 0.1f, false);
	SpriteRenderer1->CreateAnimation("Boss_RNormal", "Boss.png", 3, 0, 0.1f, false);
	SpriteRenderer1->CreateAnimation("Boss_Hit", "Boss.png", 4, 7, 0.2f);
	SpriteRenderer1->CreateAnimation("Boss_Dying", "Boss.png", 8, 11, 0.1f, false);
	SpriteRenderer1->CreateAnimation("Boss_RDying", "Boss.png", 11, 8, 0.1f, false);
	SpriteRenderer1->CreateAnimation("Boss_Death", "Boss.png", 20, 29, 0.2f, false);

	SpriteRenderer1->SetAnimationEvent("Boss_Normal", 2, [this]()
		{
			TimeEventer.PushEvent(0.1f, [this]()
				{
					if (BossState::ATTACK == CurBossState)
					{
						ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
						BossBullet->SetActorLocation({ 336, 312 });
					}
				});
			TimeEventer.PushEvent(0.6f, [this]()
				{
					if (BossState::ATTACK == CurBossState)
					{
						ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
						BossBullet->SetActorLocation({ 336, 312 });
					}
				});
			TimeEventer.PushEvent(1.1f, [this]()
				{
					if (BossState::ATTACK == CurBossState)
					{
						ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
						BossBullet->SetActorLocation({ 336, 312 });
					}
				});
			TimeEventer.PushEvent(1.6f, [this]()
				{
					if (BossState::ATTACK == CurBossState)
					{
						ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
						BossBullet->SetActorLocation({ 336, 312 });
					}
				});
			TimeEventer.PushEvent(2.1f, [this]()
				{
					if (BossState::ATTACK == CurBossState)
					{
						ABossBullet* BossBullet = GetWorld()->SpawnActor<ABossBullet>();
						BossBullet->SetActorLocation({ 336, 312 });
						SpriteRenderer1->ChangeAnimation("Boss_RNormal");
					}
				});
		});
	
	SpriteRenderer1->SetAnimationEvent("Boss_RNormal", 0, [this]()
		{
			ChangeBossState(BossState::IDLE);
			BossAttack = true;
		});

	SpriteRenderer1->SetAnimationEvent("Boss_Death", 29, [this]()
		{
			this->AActor::Destroy();
		});


	SpriteRenderer2 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer2->SetSprite("Boss_Brick.png");
	SpriteRenderer2->SetComponentScale({ 144, 280 });
	SpriteRenderer2->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer2->SetComponentLocation(SpriteRenderer2->GetComponentLocation());

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 144, 280 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Boss);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);
}

ABoss::~ABoss()
{
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("BossHP : " + std::to_string(BossHP));
	UEngineDebug::CoreOutPutString("CurIndex : " + std::to_string(SpriteRenderer1->GetCurSpriteIndex()));

	if (0 == BossHP && true != BossDeath)
	{
		BossDeath = true;
		ChangeBossState(BossState::DESTROY);

	}

	switch (CurBossState)
	{
	case BossState::IDLE:
		Idle(_DeltaTime);
		break;
	case BossState::ATTACK:
		Attack(_DeltaTime);
		break;
	case BossState::DESTROY:
		Destroy(_DeltaTime);
		break;
	default:
		break;
	}

	ABall* ResultBall = reinterpret_cast<ABall*>(CollisionComponent->CollisionOnce(ECollisionGroup::Ball));

	FVector2D BossSize = SpriteRenderer2->GetComponentScale();
	BossTrans.Location = { GetActorLocation() };
	Ratio = (BossSize.Y / 2) / (BossSize.X / 2);

	if (nullptr != ResultBall)
	{
		BallTrans.Location = { ResultBall->GetActorLocation() };
		if (BallTrans.Location.X < BossTrans.Location.X && BallTrans.Location.X >(BossTrans.Location.X - (BossSize.X / 2)) &&
			BallTrans.Location.Y > (BossTrans.Location.Y - (BossSize.Y / 2)) && BallTrans.Location.Y < BossTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BossTrans.Location.X);

			if ((Line) > (BossTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::UP);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
		}

		if (BallTrans.Location.X < BossTrans.Location.X && BallTrans.Location.X >(BossTrans.Location.X - (BossSize.X / 2)) &&
			BallTrans.Location.Y < (BossTrans.Location.Y + (BossSize.Y / 2)) && BallTrans.Location.Y > BossTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BossTrans.Location.X);

			if ((Line) < (BossTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Left");
				if (ResultBall->GetBallDir().X > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::LEFT);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
		}



		if (BallTrans.Location.X > BossTrans.Location.X && BallTrans.Location.X < (BossTrans.Location.X + (BossSize.X / 2)) &&
			BallTrans.Location.Y >(BossTrans.Location.Y - (BossSize.Y / 2)) && BallTrans.Location.Y < BossTrans.Location.Y)
		{
			Line = Ratio * (BallTrans.Location.X - BossTrans.Location.X);

			if ((Line) > (BossTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Top");
				if (ResultBall->GetBallDir().Y > 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::UP);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
		}

		if (BallTrans.Location.X > BossTrans.Location.X && BallTrans.Location.X < (BossTrans.Location.X + (BossSize.X / 2)) &&
			BallTrans.Location.Y < (BossTrans.Location.Y + (BossSize.Y / 2)) && BallTrans.Location.Y > BossTrans.Location.Y)
		{
			Line = (-Ratio) * (BallTrans.Location.X - BossTrans.Location.X);

			if ((Line) < (BossTrans.Location.Y - BallTrans.Location.Y))
			{
				UEngineDebug::OutPutString("Right");
				if (ResultBall->GetBallDir().X < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::RIGHT);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
			else
			{
				UEngineDebug::OutPutString("Bottom");
				if (ResultBall->GetBallDir().Y < 0)
				{
					FVector2D Dir;
					Dir = ResultBall->GetBallDir().Reflect(FVector2D::DOWN);

					SpriteRenderer1->SetSprite("Boss.png", SpriteRenderer1->GetCurSpriteIndex() + 4);
					BossHP -= 1;
					ResultBall->SetBallDir(Dir);
				}
			}
		}
	}
}

void ABoss::Idle(float _DeltaTime)
{
	CountTime += _DeltaTime;

	if (2.0f < CountTime)
	{
		ChangeBossState(BossState::ATTACK);
		CountTime = 0.0f;
	}
}

void ABoss::Attack(float _DeltaTime)
{
	if (true == BossAttack)
	{
		BossAttack = false;
		SpriteRenderer1->ChangeAnimation("Boss_Normal");
	}
}

void ABoss::Destroy(float _DeltaTime)
{
	SpriteRenderer1->ChangeAnimation("Boss_Death");
}

