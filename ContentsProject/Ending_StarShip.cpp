#include "PreCompile.h"
#include "Ending_StarShip.h"

#include <EngineCore/SpriteRenderer.h>


AEnding_StarShip::AEnding_StarShip()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("StarShip.png");
	SpriteRenderer->SetComponentScale({ 573, 249 });
	SpriteRenderer->CreateAnimation("StarShip", "StarShip.png", 0, 1, 0.1f);
	SpriteRenderer->CreateAnimation("StarShip_Broken", "StarShip.png", 2, 6, 0.2f, false);
	SpriteRenderer->CreateAnimation("StarShip_RBroken", "StarShip.png", 6, 2, 0.2f, false);

	SpriteRenderer->SetAnimationEvent("StarShip_Broken", 5, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_RBroken");
		});

	SpriteRenderer->SetAnimationEvent("StarShip_RBroken", 5, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_Broken");
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

