#include "PreCompile.h"
#include "Score.h"
#include "Player.h"

AScore::AScore()
{
	for (size_t i = 0; i < 10; i++)
	{
		// 카메라가 움직여도 이녀석은 움직이지 않는다.
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}


AScore::~AScore()
{
}

void AScore::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AScore::BeginPlay()
{
	Super::BeginPlay();
	Vaus = GetWorld()->GetPawn<APlayer>();
}

void AScore::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	switch (ScoreType)
	{
	case EScoreType::SCORE:
		SetValue(Vaus->GetPlayerScore());
		break;
	case EScoreType::HIGHSCORE:
		if (HighScore > Vaus->GetPlayerScore())
		{
			SetValue(HighScore);
		}
		else
		{
			SetValue(Vaus->GetPlayerScore());
		}
		break;
	default:
		break;
	}
}

void AScore::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void AScore::SetValue(int _Score = 0)
{
	std::string Number = std::to_string(_Score);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	for (int i = static_cast<int>(Number.size()) - 1; i >= 0; i--)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X -= TextScale.X;
		Renders[i]->SetActive(true);
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}

}