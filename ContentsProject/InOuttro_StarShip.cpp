#include "PreCompile.h"
#include "InOuttro_StarShip.h"

#include <EngineCore/SpriteRenderer.h>


AInOuttro_StarShip::AInOuttro_StarShip()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 573, 249 });
	SpriteRenderer->CreateAnimation("StarShip", "StarShip.png", 0, 1, 0.1f);
	SpriteRenderer->CreateAnimation("StarShip_Broken", "StarShip.png", 2, 6, 0.2f, false);
	SpriteRenderer->CreateAnimation("StarShip_RBroken", "StarShip.png", 6, 2, 0.2f, false);
	SpriteRenderer->CreateAnimation("StarShip_Open", "StarShip.png", 7, 19, 0.2f, false);
	SpriteRenderer->CreateAnimation("StarShip_Close", "StarShip.png", 19, 7, 0.2f, false);

	SpriteRenderer->SetAnimationEvent("StarShip_Broken", 5, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_RBroken");
		});

	SpriteRenderer->SetAnimationEvent("StarShip_RBroken", 5, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_Broken");
		});

	SpriteRenderer->SetAnimationEvent("StarShip_Open", 19, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip_Close");
		});

	SpriteRenderer->SetAnimationEvent("StarShip_Close", 7, [this]()
		{
			SpriteRenderer->ChangeAnimation("StarShip");
		});
	//SpriteRenderer->SetAnimationEvent("StarShip_Broken", 5, [this]()
	//	{
	//		SpriteRenderer->ChangeAnimation("StarShip_RBroken");
	//	});
}

AInOuttro_StarShip::~AInOuttro_StarShip()
{
}

void AInOuttro_StarShip::BeginPlay()
{
	Super::BeginPlay();

	switch (StarShipType)
	{
	case EInOuttro_StarShip::NONE:
		break;
	case EInOuttro_StarShip::INTRO:
		SpriteRenderer->ChangeAnimation("StarShip");
		break;
	case EInOuttro_StarShip::OUTTRO:
		SpriteRenderer->ChangeAnimation("StarShip_Broken");
		break;
	default:
		break;
	}
}

void AInOuttro_StarShip::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

