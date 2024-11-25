#include "PreCompile.h"
#include "Intro_Enemies.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>


AIntro_Enemies::AIntro_Enemies()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//SpriteRenderer->SetSprite("StarShip.png");
	SpriteRenderer->SetComponentScale({ 64, 64 });
	SpriteRenderer->CreateAnimation("Intro_Enemies", "Intro_Enemies.png", 0, 15, 0.2f, false);
	SetActorLocation(P0);
}

AIntro_Enemies::~AIntro_Enemies()
{
}

void AIntro_Enemies::BeginPlay()
{
	Super::BeginPlay();
	SpriteRenderer->ChangeAnimation("Intro_Enemies");
}

void AIntro_Enemies::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckTime += 0.00035f;

	Bezier.Bezier3(CheckTime, P0, P1, P2, P3);

	SetActorLocation(Bezier);

}

