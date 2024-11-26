#include "PreCompile.h"
#include "InOuttro_LaserEffect.h"

#include <EngineCore/SpriteRenderer.h>


AInOuttro_LaserEffect::AInOuttro_LaserEffect()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 128, 96 });
	SpriteRenderer->CreateAnimation("Intro_LaserEffect", "InOuttro_LaserEffect.png", 0, 8, 0.1f, false);
	SpriteRenderer->CreateAnimation("Outtro_LaserEffect", "InOuttro_LaserEffect.png", 8, 0, 0.1f, false);

	SpriteRenderer->SetAnimationEvent("Intro_LaserEffect", 8, [this]()
		{
			this->AActor::Destroy();
		});

	SpriteRenderer->SetAnimationEvent("Outtro_LaserEffect", 1, [this]()
		{
			this->AActor::Destroy();
		});

}

AInOuttro_LaserEffect::~AInOuttro_LaserEffect()
{
}

void AInOuttro_LaserEffect::BeginPlay()
{
	Super::BeginPlay();

	switch (LaserEffectType)
	{
	case EInOuttro_LaserEffect::NONE:
		break;
	case EInOuttro_LaserEffect::INTRO:
		SpriteRenderer->ChangeAnimation("Intro_LaserEffect");
		break;
	case EInOuttro_LaserEffect::OUTTRO:
		SpriteRenderer->ChangeAnimation("Outtro_LaserEffect");
		break;
	default:
		break;
	}
}

void AInOuttro_LaserEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

