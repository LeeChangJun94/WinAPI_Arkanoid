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
	SpriteRenderer1->SetComponentScale({ 48, 21 });
	SpriteRenderer2->SetComponentScale(SpriteRenderer1->GetComponentScale());
	SpriteRenderer2->SetComponentLocation({ SpriteRenderer1->GetComponentLocation().X + 3.0f, SpriteRenderer1->GetComponentLocation().Y + 3.0f});
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
	CollisionComponent->SetComponentScale({ 48, 21 });
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
		(*BalliterStart)->SetBallSpeed(300.0f);
	}

	Vaus->SlowEffect = true;
	Vaus->CatchEffect = false;

	Vaus->ChangeState(PlayerState::Idle);
}

void AItem::ItemCatch()
{
	SpriteRenderer1->ChangeAnimation("Catch");
}

void AItem::ItemCatchEffect()
{
	if (true == Vaus->SlowEffect)
	{
		Vaus->SlowEffect = false;
		std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
		std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
		for (; BalliterStart != BalliterEnd; ++BalliterStart)
		{
			(*BalliterStart)->SetBallSpeed(500.0f);
		}
	}
	Vaus->CatchEffect = true;
	Vaus->ChangeState(PlayerState::Idle);
}

void AItem::ItemLaser()
{
	SpriteRenderer1->ChangeAnimation("Laser");
}

void AItem::ItemLaserEffect()
{
	if (true == Vaus->SlowEffect)
	{
		Vaus->SlowEffect = false;
		std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
		std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
		for (; BalliterStart != BalliterEnd; ++BalliterStart)
		{
			(*BalliterStart)->SetBallSpeed(500.0f);
		}
	}
	Vaus->ChangeState(PlayerState::Laser);
	Vaus->CatchEffect = false;
}

void AItem::ItemEnlarge()
{
	SpriteRenderer1->ChangeAnimation("Enlarge");
}

void AItem::ItemEnlargeEffect()
{
	if (true == Vaus->SlowEffect)
	{
		Vaus->SlowEffect = false;
		std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
		std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
		for (; BalliterStart != BalliterEnd; ++BalliterStart)
		{
			(*BalliterStart)->SetBallSpeed(500.0f);
		}
	}
	Vaus->ChangeState(PlayerState::Enlarge);
	Vaus->CatchEffect = false;
}

void AItem::ItemDisruption()
{
	SpriteRenderer1->ChangeAnimation("Disruption");
}

void AItem::ItemDisruptionEffect()
{
	UEngineRandom Random;
	if (true == Vaus->SlowEffect)
	{
		Vaus->SlowEffect = false;
		std::list<ABall*>::iterator BalliterStart = PlayerLife->BallList.begin();
		std::list<ABall*>::iterator BalliterEnd = PlayerLife->BallList.end();
		for (; BalliterStart != BalliterEnd; ++BalliterStart)
		{
			(*BalliterStart)->SetBallSpeed(500.0f);
		}
	}

	for (size_t i = PlayerLife->BallList.size(); i < 3; ++i)
	{
		float RandomValue = Random.Randomfloat(-5.0f, 5.0f);

		ABall* BallActor = GetWorld()->SpawnActor<ABall>();
		PlayerLife->BallList.push_back(BallActor);
		BallActor->SetStarTime(false);
		std::list<ABall*>::iterator Balliter = PlayerLife->BallList.begin();
		BallActor->SetActorLocation((*Balliter)->GetActorLocation());
		BallActor->SetBallDir((*Balliter)->GetBallDir().X + RandomValue, (*Balliter)->GetBallDir().Y + RandomValue);
	}
	Vaus->CatchEffect = false;
	Vaus->ChangeState(PlayerState::Idle);
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
		LifeUp = UEngineSound::Play("Item_Life.wav");
		LifeUp.SetVolume(0.2f);
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
	int RandomValue = Random.RandomInt(1, 40);
	if (28 < RandomValue)
	{
		ItemState = ModeState::None;
	}
	else if (24 < RandomValue)
	{
		ItemState = ModeState::Slow;
	}
	else if (20 < RandomValue)
	{
		ItemState = ModeState::Catch;
	}
	else if (16 < RandomValue)
	{
		ItemState = ModeState::Laser;
	}
	else if (12 < RandomValue)
	{
		ItemState = ModeState::Enlarge;
	}
	else if (8 < RandomValue)
	{
		ItemState = ModeState::Disruption;
	}
	else if (6 < RandomValue)
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
		if (true == Vaus->SlowEffect)
		{
			this->Destroy();
		}
		ItemSlow();
		break;
	case ModeState::Catch:
		if (2 <= PlayerLife->BallList.size() || true == Vaus->CatchEffect)
		{
			this->Destroy();
		}
		ItemCatch();
		break;
	case ModeState::Laser:
		if (PlayerState::Laser == Vaus->GetCurPlayerState())
		{
			this->Destroy();
		}
		ItemLaser();
		break;
	case ModeState::Enlarge:
		if (PlayerState::Enlarge == Vaus->GetCurPlayerState())
		{
			this->Destroy();
		}
		ItemEnlarge();
		break;
	case ModeState::Disruption:
		if (2 <= PlayerLife->BallList.size() || true == Vaus->CatchEffect)
		{
			this->Destroy();
		}
		ItemDisruption();
		break;
	case ModeState::Break:
		this->Destroy();
		//ItemBreak();
		break;
	case ModeState::Player:
		if (5 == PlayerLife->GetLifeCount())
		{
			this->Destroy();
		}
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

	if (true == Vaus->GetStartSwitch())
	{
		Destroy();
	}
}


