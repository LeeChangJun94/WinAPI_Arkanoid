#include "PreCompile.h"
#include "Item.h"

#include <EngineCore/SpriteRenderer.h>

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

void AItem::BeginPlay()
{

}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);





}

