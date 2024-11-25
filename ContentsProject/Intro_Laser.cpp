#include "PreCompile.h"
#include "Intro_Laser.h"
#include "Intro_LaserEffect.h"

#include <EngineCore/SpriteRenderer.h>


AIntro_Laser::AIntro_Laser()
{
	SpriteRenderer1 = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer1->SetSprite("Intro_Laser.png");
	SpriteRenderer1->SetComponentScale({ 384, 288 });
	SpriteRenderer1->CreateAnimation("Intro_Laser", "Intro_Laser.png", 0, 12, 0.1f, false);
	
	SpriteRenderer1->SetAnimationEvent("Intro_Laser", 6, [this]()
		{
			AIntro_LaserEffect* LaserEffect = GetWorld()->SpawnActor<AIntro_LaserEffect>();
			LaserEffect->SetActorLocation({ 336, 520 });
		});

	SpriteRenderer1->SetAnimationEvent("Intro_Laser", 12, [this]()
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

	SpriteRenderer1->ChangeAnimation("Intro_Laser");
}

void AIntro_Laser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

