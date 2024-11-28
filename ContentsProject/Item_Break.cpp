#include "PreCompile.h"
#include "Item_Break.h"

AItem_Break::AItem_Break()
{
	SpriteRenderer = CreateDefaultSubObject<UEngineSprite>();

}

AItem_Break::~AItem_Break()
{
}

void AItem_Break::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_Break::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

