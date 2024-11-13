#include "PreCompile.h"
#include "Item.h"
#include "Ball.h"
#include "Player.h"
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

	SpriteRenderer1->ChangeAnimation("Laser");


}

AItem::~AItem()
{
}

void AItem::ItemSlow()
{
	SpriteRenderer1->ChangeAnimation("Slow");
	ABall::Ball->SetBallSpeed(500.0f);
}

void AItem::ItemCatch()
{
	SpriteRenderer1->ChangeAnimation("Catch");
	//APlayer* Vaus = GetWorld()->GetPawn<APlayer>();
	//ABall::Ball->SetActorLocation({ Vaus->GetActorLocation().X + 5.0f, Vaus->GetActorLocation().Y - ABall::Ball->GetBallScale().Y });

	if (true == UEngineInput::GetInst().IsDown('J'))
	{
		//AddActorLocation(ABall::Ball->Dir * _DeltaTime * Speed);
	}
}

void AItem::ItemLaser()
{
	SpriteRenderer1->ChangeAnimation("Laser");
}

void AItem::ItemEnlarge()
{
	SpriteRenderer1->ChangeAnimation("Enlarge");
}

void AItem::ItemDisruption()
{
	SpriteRenderer1->ChangeAnimation("Disruption");
}

void AItem::ItemBreak()
{
	SpriteRenderer1->ChangeAnimation("Break");
}

void AItem::ItemPlayer()
{
	SpriteRenderer1->ChangeAnimation("Player");
}

ModeState AItem::RandomItemCreate()
{
	ModeState Item = ModeState::None;
	UEngineRandom Random;
	int RandomValue = Random.RandomInt(1, 100);
	if (70 < RandomValue)
	{
		Item = ModeState::None;
	}
	else if (60 < RandomValue)
	{
		Item = ModeState::Slow;
	}
	else if (50 < RandomValue)
	{
		Item = ModeState::Catch;
	}
	else if (40 < RandomValue)
	{
		Item = ModeState::Laser;
	}
	else if (30 < RandomValue)
	{
		Item = ModeState::Enlarge;
	}
	else if (20 < RandomValue)
	{
		Item = ModeState::Disruption;
	}
	else if (10 < RandomValue)
	{
		Item = ModeState::Break;
	}
	else if (0 < RandomValue)
	{
		Item = ModeState::Player;
	}
	return Item;
}


void AItem::BeginPlay()
{

}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);





}


