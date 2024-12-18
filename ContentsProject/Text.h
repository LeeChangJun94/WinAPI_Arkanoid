#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

enum class ETextValue_Index
{
	COMMA = 36,
	DOT = 37,
	DOUBLEQUOTES = 38,
	SPACE = 39,
};

// ���� :
class AText : public AActor
{
public:
	// constrcuter destructer
	AText();
	~AText();

	// delete Function
	AText(const AText& _Other) = delete;
	AText(AText&& _Other) noexcept = delete;
	AText& operator=(const AText& _Other) = delete;
	AText& operator=(AText&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetText(std::string _Text, float _Time, bool _Reverse);
	void SetText(std::string _Text, bool _Reverse);
	void SetText(int _Number, bool _Reverse);
	void ShowText(float _DeltaTime);

	int CharToTextIndex(char _C);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;
	float Time = 0.0f;
	float CurTime = 0.0f;
	int CurCount = 0;

	class APlayer* Vaus = nullptr;

};

