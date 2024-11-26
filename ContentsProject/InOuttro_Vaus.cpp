#include "PreCompile.h"
#include "InOuttro_Vaus.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>

AInOuttro_Vaus::AInOuttro_Vaus()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale({ 99, 33 });
	SpriteRenderer->CreateAnimation("Intro_Vaus", "Intro_Vaus.png", 0, 23, 0.3f, false);
	SpriteRenderer->CreateAnimation("Outtro_Vaus1", "Intro_Vaus.png", 15, 23, 0.3f, false);
	SpriteRenderer->CreateAnimation("Outtro_Vaus2", "Outtro_Vaus.png", 0, 5, 0.3f, false);

	SpriteRenderer->SetAnimationEvent("Intro_Vaus", 14, [this]()
		{
			Speed = 0.0f;
		});

	SpriteRenderer->SetAnimationEvent("Intro_Vaus", 23, [this]()
		{
			this->AActor::Destroy();
		});

	SpriteRenderer->SetAnimationEvent("Outtro_Vaus1", 23, [this]()

		{
			SpriteRenderer->SetComponentScale({ 64, 16 });
			SpriteRenderer->ChangeAnimation("Outtro_Vaus2");
		});

	SpriteRenderer->SetAnimationEvent("Outtro_Vaus2", 5, [this]()
		{
			if (true != Move)
			{
				Move = true;
			}
		});
}

AInOuttro_Vaus::~AInOuttro_Vaus()
{
}

void AInOuttro_Vaus::BeginPlay()
{
	Super::BeginPlay();

	CurTime = 0.0f;
	switch (InOuttro_Vaus)
	{
	case EInOuttro_Vaus::NONE:
		break;
	case EInOuttro_Vaus::INTRO:
		Distance = { 248.0f - GetActorLocation().X, 420.0f - GetActorLocation().Y };
		SpriteRenderer->ChangeAnimation("Intro_Vaus");
		break;
	case EInOuttro_Vaus::OUTTRO:
		Distance = { 330.0f - GetActorLocation().X, 530.0f - GetActorLocation().Y };
		SpriteRenderer->ChangeAnimation("Outtro_Vaus1");
		SetActorLocation({ 330, 230 });
		break;
	default:
		break;
	}
}

void AInOuttro_Vaus::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("CurIndex : " + std::to_string(SpriteRenderer->GetCurSpriteIndex()));

	if (EInOuttro_Vaus::INTRO == InOuttro_Vaus)
	{
		FVector2D Dir = Distance;
		Dir.Normalize();
		AddActorLocation(Dir * Speed * _DeltaTime);
	}

	if (EInOuttro_Vaus::OUTTRO == InOuttro_Vaus && true == Move)
	{
		CurTime += _DeltaTime;
		FVector2D Location = FVector2D::LerpClamp(FVector2D({ 330.0f ,230.0f }), FVector2D({ 330.0f ,550.0f }), CurTime / 2.0f);
		SetActorLocation(Location);
		if (549.0f < GetActorLocation().Y)
		{
			Destroy();
		}
	}
		
}

