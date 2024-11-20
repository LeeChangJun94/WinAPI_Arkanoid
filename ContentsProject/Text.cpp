#include "PreCompile.h"
#include "Text.h"
#include "Player.h"

AText::AText()
{
	for (size_t i = 0; i < 26; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
}

AText::~AText()
{
}

void AText::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AText::BeginPlay()
{
	Vaus = GetWorld()->GetPawn<APlayer>();
}

void AText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AText::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void AText::SetText(std::string _Text)
{
	std::string Text = _Text;

	if (Renders.size() <= Text.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	for (int i = static_cast<int>(Text.size()) - 1; i >= 0; i--)
	{
		char Value = Text[i] - 'A';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X -= TextScale.X;
		Renders[i]->SetActive(true);
	}

	for (size_t i = Text.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}

}