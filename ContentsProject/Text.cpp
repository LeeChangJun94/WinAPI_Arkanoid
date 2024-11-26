#include "PreCompile.h"
#include "Text.h"
#include "Player.h"



AText::AText()
{
	for (size_t i = 0; i < 40; i++)
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

void AText::SetText(std::string _Text, float _Time, bool _Reverse)
{
	std::string Text = _Text;

	Time = _Time;

	if (Renders.size() <= Text.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	if (false == _Reverse)
	{
		for (int i = 0; i < static_cast<int>(Text.size()); i++)
		{
			char Value = Text[i];
			int Index = CharToTextIndex(Value);
			Renders[i]->SetSprite(TextSpriteName, Index);
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X += TextScale.X;
			Renders[i]->SetActive(false);
		}
	}
	else
	{
		for (int i = static_cast<int>(Text.size()) - 1; i >= 0; i--)
		{
			char Value = Text[i];
			int Index = CharToTextIndex(Value);
			Renders[i]->SetSprite(TextSpriteName, Index);
			Renders[i]->SetComponentScale(TextScale);
			Renders[i]->SetComponentLocation(Pos);
			Pos.X -= TextScale.X;
			Renders[i]->SetActive(false);
		}
	}

	for (size_t i = Text.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
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

void AText::ShowText(float _DeltaTime)
{
	int Size = static_cast<int>(Renders.size());
	for (size_t i = 0; i < Size; i++) {
		Renders[i]->SetActive(false);
	}

	if (Time == 0.0f) {
		CurCount = Size;
	}

	CurTime += _DeltaTime;

	if (CurTime > Time) {
		++CurCount;
		CurTime = 0.0f;
	}
	if (CurCount >= Size) {
		CurCount = Size;
		Time = 0.0f;
	}

	for (size_t i = 0; i < CurCount; i++) {
		Renders[i]->SetActive(true);
	}
}

int AText::CharToTextIndex(char _C)
{
	if (_C >= 'A' && _C <= 'Z') {
		return (_C - 'A');
	}
	switch (_C)
	{
	case ',': return static_cast<int>(ETextValue_Index::COMMA);
	case '.': return static_cast<int>(ETextValue_Index::DOT);
	case '"': return static_cast<int>(ETextValue_Index::DOUBLEQUOTES);
	case ' ': return static_cast<int>(ETextValue_Index::SPACE);
	default: break;
	}
}