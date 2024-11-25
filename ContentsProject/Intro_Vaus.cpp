#include "PreCompile.h"
#include "Intro_Vaus.h"

#include <EngineCore/SpriteRenderer.h>


AIntro_Vaus::AIntro_Vaus()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("StarShip.png");
	SpriteRenderer->SetComponentScale({ 99, 33 });
	SpriteRenderer->CreateAnimation("Intro_Vaus", "Intro_Vaus.png", 0, 23, 0.3f);

	SpriteRenderer->SetAnimationEvent("Intro_Vaus", 14, [this]()
		{
			Speed = 0.0f;
		});

	SpriteRenderer->SetAnimationEvent("Intro_Vaus", 23, [this]()
		{
			this->AActor::Destroy();
		});
}
//248 420

AIntro_Vaus::~AIntro_Vaus()
{
}

void AIntro_Vaus::BeginPlay()
{
	Super::BeginPlay();
	Distance = { 248.0f - GetActorLocation().X, 420.0f - GetActorLocation().Y };
	SpriteRenderer->ChangeAnimation("Intro_Vaus");
}

void AIntro_Vaus::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	FVector2D Dir = Distance;
	Dir.Normalize();
	AddActorLocation(Dir * Speed * _DeltaTime);
}

