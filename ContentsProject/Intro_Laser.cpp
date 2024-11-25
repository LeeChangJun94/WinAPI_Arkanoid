#include "PreCompile.h"
#include "Intro_Laser.h"
#include "Intro_LaserEffect.h"
#include "Intro_Vaus.h"
#include "Intro_StarShip.h"

#include <EngineCore/SpriteRenderer.h>


AIntro_Laser::AIntro_Laser()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Intro_Laser.png");
	SpriteRenderer->SetComponentScale({ 384, 288 });
	SpriteRenderer->CreateAnimation("Intro_Laser", "Intro_Laser.png", 0, 12, 0.1f, false);
	
	SpriteRenderer->SetAnimationEvent("Intro_Laser", 6, [this]()
		{
			AIntro_LaserEffect* LaserEffect = GetWorld()->SpawnActor<AIntro_LaserEffect>();
			LaserEffect->SetActorLocation({ 320, 530 });

			AIntro_Vaus* Intro_Vaus = GetWorld()->SpawnActor<AIntro_Vaus>();
			Intro_Vaus->SetActorLocation({ 320, 530 });

			StarShip->GetSpriteRenderer()->ChangeAnimation("StarShip_Broken");
		});

	SpriteRenderer->SetAnimationEvent("Intro_Laser", 12, [this]()
		{
			this->AActor::Destroy();
		});
}

AIntro_Laser::~AIntro_Laser()
{
}

void AIntro_Laser::BeginPlay()
{
	Super::BeginPlay();

	SpriteRenderer->ChangeAnimation("Intro_Laser");
}

void AIntro_Laser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

