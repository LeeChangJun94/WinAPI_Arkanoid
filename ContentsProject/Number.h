#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ANumber : public AActor
{
public:
	// constrcuter destructer
	ANumber();
	~ANumber();

	// delete Function
	ANumber(const ANumber& _Other) = delete;
	ANumber(ANumber&& _Other) noexcept = delete;
	ANumber& operator=(const ANumber& _Other) = delete;
	ANumber& operator=(ANumber&& _Other) noexcept = delete;

	void SetNumberSpriteName(const std::string _Number);

	void SetNumberScale(FVector2D _NumberScale)
	{
		NumberScale = _NumberScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetNumber(int _Number);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string NumberSpriteName;
	FVector2D NumberScale;
	std::vector<class USpriteRenderer*> Renders;

	class APlayer* Vaus = nullptr;

};

