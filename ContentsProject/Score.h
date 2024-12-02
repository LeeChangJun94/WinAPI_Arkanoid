#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

enum class EScoreType
{
	SCORE,
	HIGHSCORE,
};

// ���� :
class AScore : public AActor
{
public:
	// constrcuter destructer
	AScore();
	~AScore();

	// delete Function
	AScore(const AScore& _Other) = delete;
	AScore(AScore&& _Other) noexcept = delete;
	AScore& operator=(const AScore& _Other) = delete;
	AScore& operator=(AScore&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	void SetScoreType(EScoreType _ScoreType)
	{
		ScoreType = _ScoreType;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetValue(int _Score);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	EScoreType ScoreType = EScoreType::SCORE;

	int HighScore = 50000;

	std::string TextSpriteName;
	FVector2D TextScale;
	std::vector<class USpriteRenderer*> Renders;

	class APlayer* Vaus = nullptr;

};

