#include "PreCompile.h"
#include "Number.h"
#include "Player.h"

ANumber::ANumber()
{
	for (size_t i = 0; i < 10; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}

ANumber::~ANumber()
{
}

void ANumber::SetNumberSpriteName(const std::string _Number)
{
	NumberSpriteName = _Number;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(NumberSpriteName);
	}
}

void ANumber::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();
}

void ANumber::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ANumber::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void ANumber::SetNumber(int _Number)
{
	std::string Number = std::to_string(_Number);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	for (int i = static_cast<int>(Number.size()) - 1; i >= 0; i--)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(NumberSpriteName, Value);
		Renders[i]->SetComponentScale(NumberScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X -= NumberScale.X;
		Renders[i]->SetActive(true);
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}

}