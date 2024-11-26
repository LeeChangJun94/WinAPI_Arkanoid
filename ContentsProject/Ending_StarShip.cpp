#include "PreCompile.h"
#include "Ending_StarShip.h"

#include <EngineCore/SpriteRenderer.h>


AEnding_StarShip::AEnding_StarShip()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 573, 249 });
	SpriteRenderer->CreateAnimation("StarShip", "StarShip.png", 0, 1, 0.1f);
	SpriteRenderer->CreateAnimation("StarShip_Open", "StarShip.png", 7, 19, 0.2f, false);
	SpriteRenderer->CreateAnimation("StarShip_Close", "StarShip.png", 19, 7, 0.2f, false);

	SpriteRenderer->SetAnimationEvent("StarShip_Open", 12, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_Close");
		});

	SpriteRenderer->SetAnimationEvent("StarShip_Close", 12, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_Open");
		});
}

AEnding_StarShip::~AEnding_StarShip()
{
}

void AEnding_StarShip::BeginPlay()
{
	Super::BeginPlay();

	SpriteRenderer->ChangeAnimation("StarShip");
}

void AEnding_StarShip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

