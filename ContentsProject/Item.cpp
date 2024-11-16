#include "PreCompile.h"
#include "Item.h"
#include "Ball.h"
#include "Player.h"
#include "PlayerLife.h"
#include "EngineBase/EngineRandom.h"

#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

AItem* AItem::Item = nullptr;

AItem::AItem()
{
	Item = this;

	SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer2 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetSprite("Item1.png");
	SpriteRenderer2->SetSprite("Item2.png");
	SpriteRenderer1->SetComponentScale({ 32, 14 });
	SpriteRenderer2->SetComponentScale(SpriteRenderer1->GetComponentScale());
	SpriteRenderer2->SetComponentLocation({ SpriteRenderer1->GetComponentLocation().X + 1.0f, SpriteRenderer1->GetComponentLocation().Y + 1.0f});
	//SetActorScale(SpriteRenderer1->GetComponentScale());
	
	SpriteRenderer1->SetOrder(1);
	SpriteRenderer2->SetOrder(0);
	SpriteRenderer1->CreateAnimation("Slow", "Item1.png", 0,   7, 0.1f);
	SpriteRenderer1->CreateAnimation("Catch", "Item1.png", 8,  15, 0.1f);
	SpriteRenderer1->CreateAnimation("Laser", "Item1.png", 16, 23, 0.1f);
	SpriteRenderer1->CreateAnimation("Enlarge", "Item1.png", 24, 31, 0.1f);
	SpriteRenderer1->CreateAnimation("Disruption", "Item1.png", 32, 39, 0.1f);
	SpriteRenderer1->CreateAnimation("Break", "Item1.png", 40, 47, 0.1f);
	SpriteRenderer1->CreateAnimation("Player", "Item1.png", 48, 55, 0.1f);

	//SpriteRenderer1->ChangeAnimation("Laser");

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale({ 32, 14 });
	CollisionComponent->SetCollisionGroup(ECollisionGroup::Item);
	CollisionComponent->SetCollisionType(ECollisionType::Rect);

	ItemState = RandomItemCreate();
}

AItem::~AItem()
{
}

void AItem::ItemSlow()
{
	SpriteRenderer1->ChangeAnimation("Slow");
}

void AItem::ItemSlowEffect()
{
	std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
	std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
	for (; BalliterStart != BalliterEnd; ++BalliterStart)
	{
		(*BalliterStart)->SetBallSpeed(500.0f);
	}
	//Ball->SetBallSpeed(500.0f);
}

void AItem::ItemCatch()
{
	SpriteRenderer1->ChangeAnimation("Catch");
	//APlayer* Vaus = GetWorld()->GetPawn<APlayer>();
	//ABall::Ball->SetActorLocation({ Vaus->GetActorLocation().X + 5.0f, Vaus->GetActorLocation().Y - ABall::Ball->GetBallScale().Y });
}

void AItem::ItemCatchEffect()
{
	//std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
	//std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
	//for (; BalliterStart != BalliterEnd; ++BalliterStart)
	//{
	//	(*BalliterStart)->BallCatch = true;
	//}

	Vaus->CatchEffect = true;

}

void AItem::ItemLaser()
{
	SpriteRenderer1->ChangeAnimation("Laser");
}

void AItem::ItemLaserEffect()
{
	Vaus->ChangeState(PlayerState::Laser);
}

void AItem::ItemEnlarge()
{
	SpriteRenderer1->ChangeAnimation("Enlarge");
}

void AItem::ItemEnlargeEffect()
{
	Vaus->ChangeState(PlayerState::Enlarge);
}

void AItem::ItemDisruption()
{
	SpriteRenderer1->ChangeAnimation("Disruption");
}

void AItem::ItemDisruptionEffect()
{
	UEngineRandom Random;
	
	for (int i = 0; i < 2; ++i)
	{
		float RandomValue = Random.Randomfloat(-1.0f, 1.0f);

		ABall* BallActor = GetWorld()->SpawnActor<ABall>();
		PlayerLife->BallList.push_back(BallActor);
		BallActor->SetStarTime(false);
		std::list<ABall*>::iterator Balliter = PlayerLife->BallList.begin();
		BallActor->SetActorLocation((*Balliter)->GetActorLocation());
		BallActor->SetBallDir((*Balliter)->GetBallDir().X + RandomValue, (*Balliter)->GetBallDir().Y + RandomValue);
	}
}

void AItem::ItemBreak()
{
	SpriteRenderer1->ChangeAnimation("Break");
}

void AItem::ItemBreakEffect()
{
}

void AItem::ItemPlayer()
{
	SpriteRenderer1->ChangeAnimation("Player");
}

void AItem::ItemPlayerEffect()
{
	if (5 > PlayerLife->GetLifeCount())
	{
		PlayerLife->SetLifeCount(1);
	}
	
	PlayerLife->LifeCheck();
}

void AItem::ItemCollisionCheck()
{
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::Vaus);

	if (nullptr != Result)
	{
		switch (ItemState)
		{
		case ModeState::Slow:
			ItemSlowEffect();
			break;
		case ModeState::Catch:
			ItemCatchEffect();
			break;
		case ModeState::Laser:
			ItemLaserEffect();
			break;
		case ModeState::Enlarge:
			ItemEnlargeEffect();
			break;
		case ModeState::Disruption:
			ItemDisruptionEffect();
			break;
		case ModeState::Break:
			ItemBreakEffect();
			break;
		case ModeState::Player:
			ItemPlayerEffect();
			break;
		default:
			break;
		}

		this->Destroy();
	}
}

ModeState AItem::RandomItemCreate()
{
	UEngineRandom Random;
	int RandomValue = Random.RandomInt(1, 100);
	if (70 < RandomValue)
	{
		ItemState = ModeState::None;
	}
	else if (60 < RandomValue)
	{
		ItemState = ModeState::Slow;
	}
	else if (50 < RandomValue)
	{
		ItemState = ModeState::Catch;
	}
	else if (40 < RandomValue)
	{
		ItemState = ModeState::Laser;
	}
	else if (30 < RandomValue)
	{
		ItemState = ModeState::Enlarge;
	}
	else if (20 < RandomValue)
	{
		ItemState = ModeState::Disruption;
	}
	else if (10 < RandomValue)
	{
		ItemState = ModeState::Break;
	}
	else if (0 < RandomValue)
	{
		ItemState = ModeState::Player;
	}
	return ItemState;
}

void AItem::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();

	switch (ItemState)
	{
	case ModeState::None:
		this->Destroy();
		break;
	case ModeState::Slow:
		ItemSlow();
		break;
	case ModeState::Catch:
		ItemCatch();
		break;
	case ModeState::Laser:
		ItemLaser();
		break;
	case ModeState::Enlarge:
		ItemEnlarge();
		break;
	case ModeState::Disruption:
		ItemDisruption();
		break;
	case ModeState::Break:
		ItemBreak();
		break;
	case ModeState::Player:
		ItemPlayer();
		break;
	default:
		break;
	}
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);

	ItemCollisionCheck();

	
	ABall* Result = reinterpret_cast<ABall*>(Vaus->GetCollisionComponent()->CollisionOnce(ECollisionGroup::Ball));
	if (nullptr != Result)
	{
		if (true == Vaus->CatchEffect)
		{
			std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
			std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
			for (; BalliterStart != BalliterEnd; ++BalliterStart)
			{
				(*BalliterStart)->BallCatch = true;
			}
			//Result->SetActorLocation({ Vaus->GetActorLocation().X, Vaus->GetActorLocation().Y });
			if (true == UEngineInput::GetInst().IsDown('J'))
			{
				Result->BallCatch = false;
			}
		}
		Result = nullptr;
	}
	
	
}


