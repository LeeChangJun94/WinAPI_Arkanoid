#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;

enum class EInOuttro_Vaus
{
	NONE,
	INTRO,
	OUTTRO,
};

// Ό³Έν :
class AInOuttro_Vaus : public AActor
{
public:
	// constrcuter destructer
	AInOuttro_Vaus();
	~AInOuttro_Vaus();

	// delete Function
	AInOuttro_Vaus(const AInOuttro_Vaus& _Other) = delete;
	AInOuttro_Vaus(AInOuttro_Vaus&& _Other) noexcept = delete;
	AInOuttro_Vaus& operator=(const AInOuttro_Vaus& _Other) = delete;
	AInOuttro_Vaus& operator=(AInOuttro_Vaus&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInOuttroType(EInOuttro_Vaus _InOuttro_Vaus)
	{
		InOuttro_Vaus = _InOuttro_Vaus;
	}

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Distance = { 0, 0 };
	EInOuttro_Vaus InOuttro_Vaus = EInOuttro_Vaus::NONE;

	bool Move = false;

	float CurTime = 0.0f;
	float Speed = 40.0f;


};

