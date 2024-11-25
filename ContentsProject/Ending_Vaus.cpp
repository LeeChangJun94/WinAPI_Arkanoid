#include "PreCompile.h"
#include "Ending_Vaus.h"

#include <EngineCore/SpriteRenderer.h>


AEnding_Vaus::AEnding_Vaus()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("StarShip.png");
	SpriteRenderer->SetComponentScale({ 64, 16 });
	SpriteRenderer->CreateAnimation("Ending_Vaus", "Ending_Vaus.png", 0, 5, 0.3f);

	SpriteRenderer->SetAnimationEvent("Ending_Vaus", 23, [this]()
		{
			this->AActor::Destroy();
		});
}
//248 420

AEnding_Vaus::~AEnding_Vaus()
{
}

void AEnding_Vaus::BeginPlay()
{
	Super::BeginPlay();
	Distance = { 248.0f - GetActorLocation().X, 420.0f - GetActorLocation().Y };
	SpriteRenderer->ChangeAnimation("Intro_Vaus");
}

void AEnding_Vaus::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D Dir = Distance;
	Dir.Normalize();
	AddActorLocation(Dir * Speed * _DeltaTime);
}

