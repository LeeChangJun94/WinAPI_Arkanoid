#include "PreCompile.h"
#include "Intro_LaserEffect.h"

#include <EngineCore/SpriteRenderer.h>


AIntro_LaserEffect::AIntro_LaserEffect()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("Intro_LaserEffect.png");
	SpriteRenderer->SetComponentScale({ 128, 96 });
	SpriteRenderer->CreateAnimation("Intro_LaserEffect", "Intro_LaserEffect.png", 0, 8, 0.1f, false);

	SpriteRenderer->SetAnimationEvent("Intro_LaserEffect", 8, [this]()
		{
			this->AActor::Destroy();
		});
}

AIntro_LaserEffect::~AIntro_LaserEffect()
{
}

void AIntro_LaserEffect::BeginPlay()
{
	Super::BeginPlay();
	SpriteRenderer->ChangeAnimation("Intro_LaserEffect");
}

void AIntro_LaserEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

