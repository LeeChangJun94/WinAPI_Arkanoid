#include "PreCompile.h"
#include "InOuttro_Laser.h"
#include "InOuttro_LaserEffect.h"
#include "InOuttro_Vaus.h"
#include "InOuttro_StarShip.h"

#include <EngineCore/SpriteRenderer.h>


AInOuttro_Laser::AInOuttro_Laser()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("InOuttro_Laser.png");
	SpriteRenderer->SetComponentScale({ 384, 288 });
	SpriteRenderer->CreateAnimation("Intro_Laser", "InOuttro_Laser.png", 0, 12, 0.1f, false);
	SpriteRenderer->CreateAnimation("Outtro_Laser", "InOuttro_Laser.png", 12, 0, 0.1f, false);
	
	SpriteRenderer->SetAnimationEvent("Intro_Laser", 6, [this]()
		{
			AInOuttro_LaserEffect* LaserEffect = GetWorld()->SpawnActor<AInOuttro_LaserEffect>();
			LaserEffect->SetActorLocation({ 320, 530 });
			LaserEffect->SetInOuttroType(EInOuttro_LaserEffect::INTRO);

			AInOuttro_Vaus* Intro_Vaus = GetWorld()->SpawnActor<AInOuttro_Vaus>();
			Intro_Vaus->SetActorLocation({ 320, 530 });
			Intro_Vaus->SetInOuttroType(EInOuttro_Vaus::INTRO);

			StarShip->GetSpriteRenderer()->ChangeAnimation("StarShip_Broken");
		});

	SpriteRenderer->SetAnimationEvent("Outtro_Laser", 11, [this]()
		{
			AInOuttro_LaserEffect* LaserEffect = GetWorld()->SpawnActor<AInOuttro_LaserEffect>();
			LaserEffect->SetActorLocation({ 320, 530 });
			LaserEffect->SetInOuttroType(EInOuttro_LaserEffect::OUTTRO);

			//AIntro_Vaus* Intro_Vaus = GetWorld()->SpawnActor<AIntro_Vaus>();
			//Intro_Vaus->SetActorLocation({ 320, 530 });

			StarShip->GetSpriteRenderer()->ChangeAnimation("StarShip");
		});

	SpriteRenderer->SetAnimationEvent("Intro_Laser", 12, [this]()
		{
			this->AActor::Destroy();
		});

	SpriteRenderer->SetAnimationEvent("Outtro_Laser", 1, [this]()
		{
			this->AActor::Destroy();
		});
}

AInOuttro_Laser::~AInOuttro_Laser()
{
}

void AInOuttro_Laser::BeginPlay()
{
	Super::BeginPlay();

	switch (LaserType)
	{
	case EInOuttro_Laser::NONE:
		break;
	case EInOuttro_Laser::INTRO:
		SpriteRenderer->ChangeAnimation("Intro_Laser");
		break;
	case EInOuttro_Laser::OUTTRO:
		SpriteRenderer->ChangeAnimation("Outtro_Laser");
		break;
	default:
		break;
	}
	
}

void AInOuttro_Laser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

