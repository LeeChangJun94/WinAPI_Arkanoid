#include "PreCompile.h"
#include "InOuttro_Enemies.h"
#include "InOuttro_Laser.h"

#include <EngineCore/SpriteRenderer.h>


AInOuttro_Enemies::AInOuttro_Enemies()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 64, 64 });
	SpriteRenderer->CreateAnimation("Intro_Enemies", "InOuttro_Enemies.png", 0, 15, 0.2f, false);
	SpriteRenderer->CreateAnimation("Outtro_Enemies", "InOuttro_Enemies.png", 15, 0, 0.2f, false);

	SpriteRenderer->SetAnimationEvent("Intro_Enemies", 5, [this]()
		{
			Laser = GetWorld()->SpawnActor<AInOuttro_Laser>();
			Laser->SetActorLocation({ 440, 420 });
			Laser->SetInOuttroType(EInOuttro_Laser::INTRO);
			Laser->SetStarShip(StarShip);
		});

	SpriteRenderer->SetAnimationEvent("Outtro_Enemies", 11, [this]()
		{
			Laser = GetWorld()->SpawnActor<AInOuttro_Laser>();
			Laser->SetActorLocation({ 440, 420 });
			Laser->SetInOuttroType(EInOuttro_Laser::OUTTRO);
			Laser->SetStarShip(StarShip);
		});

	//TimeEventer.PushEvent(4.1f, [this]()
	//	{
	//		Laser = GetWorld()->SpawnActor<AIntro_Laser>();
	//		Laser->SetActorLocation({ 440, 420 });
	//		Laser->SetStarShip(Intro_StarShip);
	//	});
}

AInOuttro_Enemies::~AInOuttro_Enemies()
{
}

void AInOuttro_Enemies::BeginPlay()
{
	Super::BeginPlay();

	switch (EnemiesType)
	{
	case EInOuttro_Enemies::NONE:
		break;
	case EInOuttro_Enemies::INTRO:
		SpriteRenderer->ChangeAnimation("Intro_Enemies");
		break;
	case EInOuttro_Enemies::OUTTRO:
		SpriteRenderer->ChangeAnimation("Outtro_Enemies");
		break;
	default:
		break;
	}
}

void AInOuttro_Enemies::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (EInOuttro_Enemies::INTRO == EnemiesType)
	{
		CheckTime += _DeltaTime;

		Bezier.Bezier3(CheckTime/3.0f, P0, P1, P2, P3);

		SetActorLocation(Bezier);
	}

	if (EInOuttro_Enemies::OUTTRO == EnemiesType)
	{
		CheckTime += _DeltaTime;

		Bezier.Bezier3(1 - (CheckTime / 3.0f), P0, P1, P2, P3);

		SetActorLocation(Bezier);
	}

}

